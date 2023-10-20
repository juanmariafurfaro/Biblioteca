#include <iostream>
#include<list>
#include <string>
#include <ctime>
using namespace std;
class Libro {
private:
    int id;
    string titulo;
    string autor;
    bool dispnibilidad;
public:
    Libro(int ID,string &titu,string &nomb){
        id=ID;
        titulo=titu;
        autor=nomb;
        dispnibilidad= true;
    }
    void mostrar(){
        if (dispnibilidad == false){
            cout<<"Titulo: "<<titulo<<"\tAutor: "<<autor<<"\tID: "<<id<<" (No disponible)"<<endl;
        }else {
            cout<<"Titulo: "<<titulo<<"\tAutor: "<<autor<<"\tID: "<<id<<" (Disponible)"<<endl;
        }
    }
    bool getDisponibilidad() const{
        return dispnibilidad;
    }
    void setDisponibilidad(){
        if(dispnibilidad){
            dispnibilidad= false;
        } else {
            dispnibilidad = true;
        }
    }
    int getID() const{
        return id;
    }
};
class Usuario{
private:
    int id;
    string nombre;
    bool esVip;
    int maxPrestamos;
    int prestamosActuales;
public:
    Usuario(int ID,string &nomb,bool vip,int max){
        id=ID;
        nombre=nomb;
        esVip=vip;
        maxPrestamos=max;
        prestamosActuales=0;
    }
    void mostrar(){
        if(esVip)
            cout<<"Nombre: "<<nombre<<"\tID: "<<id<<"\tCliente VIP\tPrestamos actuales: "<<prestamosActuales<<"\tMax.Prestamos: "<<maxPrestamos<<endl;
        else
            cout<<"Nombre: "<<nombre<<"\tID: "<<id<<"\tCliente no VIP\tPrestamos actuales: "<<prestamosActuales<<"\tMax.Prestamos: "<<maxPrestamos<<endl;
    }
    int getID() const{
        return id;
    }
    int getPrestamosActuales() const{
        return prestamosActuales;
    }
    int getMaxPrestamos() const{
        return maxPrestamos;
    }
    void aumentarPrestamos(){
        prestamosActuales=prestamosActuales+1;
    }
    void disminuirPrestamos(){
        prestamosActuales=prestamosActuales-1;
    }
};
class Prestamo{
private:
    int id;
    time_t fechaInicio;
    time_t fechaFin;
    Libro *libro;
    Usuario* usuario;
public:
    Prestamo(int ID,time_t inicio,time_t fin,Libro &aux,Usuario&aux2){
        id=ID;
        fechaInicio=inicio;
        fechaFin=fin;
        libro=&aux;
        usuario=&aux2;
    }
    void mostrar(){
        cout<<".................................................................................................."<<endl;
        cout<<"\nID del prestamo: "<<id<<"\n\nFecha de Inicio: "<<ctime(&fechaInicio)<<"Fecha de Fin: "<<ctime(&fechaFin)<<endl;
        cout<<"Informacion del usuario al que se le realizo el prestamo: "<<endl;
        usuario->mostrar();
        cout<<"\nInformacion del Libro que se presto: "<<endl;
        libro->mostrar();
        cout<<".................................................................................................."<<endl;
    }
    int getID() const{
        return id;
    }
    time_t getFechaFin() const{
        return fechaFin;
    }
    void definirNombre(){
        usuario->disminuirPrestamos();
        libro->setDisponibilidad();
    }

};

class Biblioteca
{
private:
    list <Libro> libros;
    list <Usuario> usuarios;
    list <Prestamo> prestamos;
public:
    void agregarLibro(Libro & newLibro){
        libros.push_back(newLibro);
    }
    void agregarUsuario(Usuario & newUsuario){
        usuarios.push_back(newUsuario);
    }
    void librosDiponibles(){
        if(libros.empty()){
            cout<<"No hay Libros registrados"<<endl;
        } else {
            cout<<"\nLista de libros: "<<endl; }
        auto it=libros.begin();
        while (it!=libros.end()){
            it->mostrar();
            *it++;
        }
    }
    void usuariosRegistrados(){
        if(usuarios.empty()){
            cout<<"No hay usuarios registrados"<<endl;
        } else {
            cout<<"\nLista de usuarios registrados: "<<endl; }
        auto it=usuarios.begin();
        while (it!=usuarios.end()){
            it->mostrar();
            *it++;
        }
    }
    void prestamosActuales(){
        if(prestamos.empty()){
            cout<<"No hay prestamos registrados"<<endl;
        }
        auto it=prestamos.begin();
        while (it!=prestamos.end()){
            it->mostrar();
            *it++;
        }
    }
    bool buscarUsuario(int aux){
        int id;
        auto it=usuarios.begin();
        while (it!=usuarios.end()){
            id=it->getID();
            *it++;
            if(aux==id)
                return true;
        }
        return false;
    }
    Usuario *obtenerUsuario(int aux){
        for (auto & usuario : usuarios) {
            if (aux == usuario.getID()) {
                Usuario *usuario1=&usuario;
                return usuario1;  // Retorna el objeto Libro encontrado
            }
        }

        // Lanza una excepción para indicar que el libro no se encontró
        throw runtime_error("Libro no encontrado");
    }
    bool buscarLibro(int aux){
        int id;
        auto it=libros.begin();
        while (it!=libros.end()){
            id=it->getID();
            *it++;
            if(aux==id)
                return true;
        }
        return false;
    }
    Libro *obtenerLibro(int aux) {
        for (auto & libro : libros) {
            if (aux == libro.getID()) {
                Libro * libro1 =&libro;
                return libro1;  // Retorna el objeto Libro encontrado
            }
        }

        // Lanza una excepción para indicar que el libro no se encontró
        throw runtime_error("Libro no encontrado");
    }
    bool buscarPestamo(int aux){
        int id;
        auto it=prestamos.begin();
        while (it!=prestamos.end()){
            id=it->getID();
            *it++;
            if(aux==id)
                return true;
        }
        return false;
    }
    Prestamo obtenerPrestamo(int aux) {
        for (auto & prestamo : prestamos) {
            if (aux == prestamo.getID()) {
                return prestamo;  // Retorna el objeto Libro encontrado
            }
        }

        // Lanza una excepción para indicar que el libro no se encontró
        throw runtime_error("prestamo no encontrado");
    }
    void hacerPrestamo(int idpres,Usuario &usu,Libro &lib,time_t fi,time_t ff){
        int pA,pM;
        pA=usu.getPrestamosActuales();
        pM=usu.getMaxPrestamos();
        bool answer=lib.getDisponibilidad();
        if(pA<pM && answer) {
            lib.setDisponibilidad();
            usu.aumentarPrestamos();
            cout<<"\n------Prestamo exitoso------"<<endl;
            Prestamo newPrestamo(idpres, fi, ff, lib, usu);
            prestamos.push_back(newPrestamo);
        }else{
            if(pA==pM)
                cout<<"\nNo se puede realizar el prestamo, porque alcanzo el limite\n";
            else
                cout<<"\nNo se puede realizar el prestamo, porque el libro no esta disponible\n2";
        }
    }
    float calcularMulta(time_t ff, time_t actual){
        time_t diferencia=actual-ff;
        float recargo=(float ) diferencia/86400;
        return recargo;
    }
    void devolverPrestamo(int idpres, Prestamo &prestamo){
        time_t fechaActualTime = time(nullptr);
        time_t fechaLimite = prestamo.getFechaFin();
        if(fechaActualTime>fechaLimite){
            float recargo=calcularMulta(fechaLimite, fechaActualTime);
            cout<<"\nUsted sobrepaso el limite de tiempo de: "<<static_cast<int>(recargo)<<" dias, debe abonar: $"<<static_cast<int>(recargo*10)<<" "<<endl;
        }
        prestamo.definirNombre();
        auto it=prestamos.begin();
        while (it!=prestamos.end()){
            if(idpres==it->getID()){
                prestamos.erase(it);
                break;
            }
            *it++;
        }
    }


};
int generadordeID(const string& nom){
    int n = 0;
    for(char caracter:nom){
        n += static_cast<int>(caracter);
    }
    return n;
}

void menu(Biblioteca &biblioteca){
    int respuesta, sum=1;
    cout << "\n--------------------------------------------------------------" <<endl;
    cout<<"Bienvenido a la biblioteca. Por favor, seleccione una opcion: "<<endl;
    cout << "--------------------------------------------------------------" <<endl;
    cout<<"1 - Ingresar un usuario nuevo\n2 - Agregar un libro\n3 - Registrar un prestamo nuevo\n4 - Mostrar el estado de los usuarios\n5 - Mostrar los libros de la biblioteca\n6 - Mostrar prestamos actuales\n7 - Devolver prestamo\n8 - Salir\n\nRespuesta:"<<" ";
    cin>>respuesta;
    while (respuesta!=8)
    {
        if (respuesta==1)
        {
            int id,maxPrestamos;
            char aux;
            string nombre;
            bool vip;
            cout<<"\nIngrese el nombre del usuario: ";
            fflush(stdin);
            getline(cin,nombre);
            id=generadordeID(nombre);
            cout<<"Es un cliente vip(V/F): ";
            cin>>aux;
            while(aux!='f' && aux!='v' && aux!='V' && aux!='F'){
                cout<<"Error.Es un cliente vip(V/F): ";
                cin>>aux;
            }
            if(aux=='v' || aux=='V'){
                vip=true;
                maxPrestamos=10;
            }else{
                vip=false;
                maxPrestamos=5;
            }
            Usuario newUsuario(id,nombre,vip,maxPrestamos);
            biblioteca.agregarUsuario(newUsuario);
        } else if (respuesta==2)
        {
            int id;
            string nombre,autor;
            cout<<"\nIngrese el nombre del libro: ";
            fflush(stdin);
            getline(cin,nombre);
            cout<<"Ingrese el autor del libro: ";
            getline(cin,autor);
            id=generadordeID(nombre);
            Libro newlibro(id,nombre,autor);
            biblioteca.agregarLibro(newlibro);
        }else if(respuesta==3){
            biblioteca.usuariosRegistrados();
            // Obtener la hora actual
            time_t inicio = time(nullptr);
            // Calcular la hora límite (15 días después)
            time_t fechaLimite = inicio + 15 * 24 * 60 * 60; // 15 días en segundos (24 horas * 60 minutos * 60 segundos)
            // Convertir los tiempos a estructuras tm para obtener información más detallada si es necesario
            time_t fechaInicioTime = inicio;
            time_t fechaLimiteTime = fechaLimite;
            int idUSU,idLibro;
            cout<<"\nIngrese su ID de usuario: ";
            cin>>idUSU;
            while (!biblioteca.buscarUsuario(idUSU))
            {
                cout<<"\nError.Ingrese su ID de usuario: ";
                cin>>idUSU;
            }
            biblioteca.librosDiponibles();
            cout<<"\nIngrese el ID del Libro: ";
            cin>>idLibro;
            while (!biblioteca.buscarLibro(idLibro))
            {
                cout<<"\nError.Ingrese su ID de libro: ";
                cin>>idLibro;
            }
            Libro *auxL = biblioteca.obtenerLibro(idLibro);
            Usuario *auxU= biblioteca.obtenerUsuario(idUSU);
            sum++;
            biblioteca.hacerPrestamo(sum,*auxU,*auxL,fechaInicioTime,fechaLimiteTime);
        }else if(respuesta==4){
            biblioteca.usuariosRegistrados();
        }else if(respuesta==5){
            biblioteca.librosDiponibles();
        }else if(respuesta==6){
            biblioteca.prestamosActuales();
        }else if (respuesta==7){
            biblioteca.prestamosActuales();
            int idPrestamo;
            cout<<"\nIngrese el ID del prestamo: ";
            cin>>idPrestamo;
            while (!biblioteca.buscarPestamo(idPrestamo))
            {
                cout<<"\nError.Ingrese el ID de su Prestamo: ";
                cin>>idPrestamo;
            }
            Prestamo aux=biblioteca.obtenerPrestamo(idPrestamo);
            biblioteca.devolverPrestamo(idPrestamo,aux);
            cout<<"\n------Libro devuelto exitosamente------\n"<<endl;
        }else if(respuesta==8){
            break;
        } else{
            cout<<"Respuesta no valida\n";
        }
        cout<<""<<endl;
        system("PAUSE");
        cout << "\n--------------------------------------------------------------" <<endl;
        cout<<"Bienvenido a la biblioteca. Por favor, seleccione una opcion: "<<endl;
        cout << "--------------------------------------------------------------" <<endl;
        cout<<"1 - Ingresar un usuario nuevo\n2 - Agregar un libro\n3 - Registrar un prestamo nuevo\n4 - Mostrar el estado de los usuarios\n5 - Mostrar los libros de la biblioteca\n6 - Mostrar prestamos actuales\n7 - Devolver prestamo\n8 - Salir\n\nRespuesta:"<<" ";
        cin>>respuesta;
    }
}


int main(){
    Biblioteca Ateneo;
    menu(Ateneo);
    return 0;
}