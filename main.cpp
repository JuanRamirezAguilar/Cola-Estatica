#include <iostream>

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

#define TAM 3

using namespace std;

class Constancia {

    private:

        string nombre;
        string carrera;
        int totalMaterias;
        float promedio;

    public:

        Constancia(){nombre = "", carrera = ""; totalMaterias = 0; promedio = 0;}
        void setNombre(string aux){nombre = aux;}
        void setCarrera(string aux){carrera = aux;}
        void setTotalMaterias(int aux){totalMaterias = aux;} 
        void setPromedio(float aux){promedio = aux;}
        string getNombre(){return nombre;}
        string getCarrera(){return carrera;}
        int getTotalMaterias(){return totalMaterias;}
        float getPromedio(){return promedio;}

        friend ostream& operator << (ostream& out, const Constancia& x){
            out << "Estudiante: " << x.nombre <<endl;
            out << "Carrera: " << x.carrera <<endl;
            out << "Total de materias: " << x.totalMaterias <<endl;
            out << "Promedio: " << x.promedio <<endl;
            return out;
        }

        Constancia &operator = (const Constancia x) {
            nombre = x.nombre;
            carrera = x.carrera;
            totalMaterias = x.totalMaterias;
            promedio = x.promedio;
            return *this;
        }

};

template <class DATO>
class Cola {
    
    private:

        DATO datos[TAM];
        int ult;

        bool inserta(DATO, int);
        bool elimina(int);
        const DATO recupera(int);
        int primero()const;
        int ultimo()const;
        void imprime()const;

    public:


        Cola(){ult = -1;}
        bool vacia()const;
        bool llena();
        bool queue(DATO&);
        bool dequeue();
        const DATO front();
        void muestra();

};

template <class DATO>
const DATO Cola <DATO>::front() {
    DATO x = datos[primero()];
    return x;
}

template <class DATO>
bool Cola <DATO>::dequeue() {
    if (vacia()) {
        return false;
    }
    else {
        elimina(primero());
    }
    return true;
}

template <class DATO>
bool Cola <DATO>::queue(DATO& elem) {
    if (llena()) {
        return false;
    }
    if (vacia()) {
        inserta(elem, 0);
    }
    else {
        inserta(elem, ultimo() + 1);
    }
    return true;
}

template <class DATO>
void Cola <DATO>::imprime()const {
    if (!vacia()) {
        for (int i = 0; i <= ult; i++) {
            Constancia x = datos[i];
            cout << i << ") ._ " << endl << x <<endl<<endl;
        }
    }
}

template <class DATO>
bool Cola <DATO>::vacia()const {
    if (ult == -1){
        return true;
    }
    else {
        return false;
    }
}

template <class DATO>
bool Cola <DATO>::llena() {
    return ult == TAM - 1;
}

template <class DATO>
bool Cola <DATO>::inserta(DATO elem, int pos) {
    if (llena() || pos < 0 || pos > ult + 1) {
        cout << endl << "No se pudo insertar...";
        return false;
    }
    int i = ult + 1;
    while (i > pos) {
        datos[i] = datos[i - 1];
        i--;
    }
    datos[pos] = elem;
    ult++;
    return true;
}

template <class DATO>
bool Cola <DATO>::elimina(int pos) {
    if(vacia() || pos < 0 || pos > ult){
        cout << endl << "No se pudo eliminar...";
        return false;
    }
    int i = pos;
    while(i < ult){
        datos[i] = datos[i + 1];
        i++;
    }
    ult--;
    return true;
}

template <class DATO>
const DATO Cola <DATO>::recupera(int pos) {
    if(vacia() || pos < 0 || pos > ult - 1){
        cout << endl << "Insuficiencia de datos...";
        //Manejar exceptions
    }
    else {
        return datos[pos];
    }
}

template<class DATO>
int Cola <DATO>::primero()const {
    if(vacia()){
       return -1;
    }
    return 0;
}

template<class DATO>
int Cola <DATO>::ultimo()const {
    if(vacia()){
       return -1;
    }
    else {
        return ult;
    }
}

template<class DATO>
void Cola <DATO>::muestra() {
    imprime();
}

void pausa () {
    std::cin.clear(); std::cin.sync(); std::cin.ignore();
}

void limpiaBuffer (void) {
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

int main () {

    Cola <Constancia> estudiantes;

    short opc;

    do {

        system(CLEAR);
        cout << "***DIRECCION ESCOLAR***" <<endl<<endl;

        cout << "Que opcion quieres elegir?" <<endl<<endl;
        cout << "1) Dar de alta a un alumno." <<endl;
        cout << "2) Elaborar una constancia." <<endl;
        cout << "3) Mostrar las constancias pendientes." <<endl;
        cout << "0) Salir." <<endl<<endl;
        cout << "Tu opcion >> ";
        cin >> opc;

        switch (opc) {

            case 0: break;
            
            case 1:{

                Constancia constAlta;
                string auxNombre, auxCarrera;
                int auxInt;
                float auxFloat;

                system(CLEAR);
                cout << "***DIRECCION ESCOLAR***" <<endl;
                cout << "***ALTA DE CONSTANCIA***" <<endl<<endl;

                cout << "Nombre del alumno: ";
                limpiaBuffer();
                getline(cin, auxNombre);

                cout << "Carrera que estudia: ";
                fflush(stdin);
                getline(cin, auxCarrera);

                cout << "Total de materias en el semestre: ";
                cin >> auxInt;

                cout << "Promedio del Alumno: ";
                cin >> auxFloat;

                constAlta.setNombre(auxNombre);
                constAlta.setCarrera(auxCarrera);
                constAlta.setTotalMaterias(auxInt);
                constAlta.setPromedio(auxFloat);

                bool alta = estudiantes.queue(constAlta);

                if (alta) {
                    cout << endl << "Registro exitoso...";
                    pausa();
                }
                else {
                    cout << endl << "Error al encolar el alta...";
                    pausa();
                }
            }break;
        
            case 2:

                if (estudiantes.vacia()){
                    system(CLEAR);    
                    cout << "***DIRECCION ESCOLAR***" <<endl;
                    cout << "***CONSTANCIA DEL ALUMNO***" <<endl<<endl;

                    cout << "No hay solicitudes pendientes...";
                    pausa();
                }
                else {
                    system(CLEAR);
                    cout << "***DIRECCION ESCOLAR***" <<endl;
                    cout << "***CONSTANCIA DEL ALUMNO***" <<endl<<endl;

                    Constancia constAux = estudiantes.front();

                    cout << "Se va a emitir la siguiente constancia: " <<endl<<endl;
                    cout << "El siguiente alumno cursa actualmente en la Universidad de Guadalajara: " <<endl;
                    cout << "Nombre del interesado: " << constAux.getNombre() << "." <<endl;
                    cout << "Carrera que estudia: " << constAux.getCarrera() << "." <<endl;
                    cout << "Total de materias que cursa actualmente: " << constAux.getTotalMaterias() << "." <<endl;
                    cout << "Promedio del estudiante: " << constAux.getPromedio() << "." <<endl<<endl;

                    cout << "Al ser emitida, la solicitud sera borrada...";
                    pausa();

                    bool borrado = estudiantes.dequeue();

                    if (borrado) {
                        cout <<endl<<endl << "Soliciutd borrada...";
                        pausa();
                    }
                    else {
                        cout << "No se pudo borrar la solicitud, intentelo de nuevo...";
                        pausa();
                    }
                }

            break;

            case 3:
                
                if (estudiantes.vacia()) {
                    system(CLEAR);
                    cout << "***DIRECCION ESCOLAR***" <<endl;
                    cout << "***SOLICITUDES DE CONSTANCIAS***" <<endl<<endl;
                    cout << "Error, no hay datos...";
                    pausa();
                }
                else {
                    system(CLEAR);
                    cout << "***DIRECCION ESCOLAR***" <<endl;
                    cout << "***SOLICITUDES DE CONSTANCIAS***" <<endl<<endl;
                    estudiantes.muestra();
                    pausa();
                }

            break;
            
            default:

                cout << endl << "Opcion erronea, intentalo de nuevo";
                pausa();

            break;
        }

    } while (opc != 0);

    return 0;

}