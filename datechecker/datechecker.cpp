
#include <iostream>
#include <string>
#include <regex>

using namespace std;

class date {
private:
    string fecha;
    int anio, mes, dia;
    int tipo;//  0. mal , 1. dia/mes/anio , 2. anio/dia/mes 
public:
    date(string fecha) {
        this->fecha = fecha;
    }

    string getFecha() {
        return fecha;
    }
    void setFecha(string fecha) {
        this->fecha = fecha;
    }
    void setAnio(int anio) {
        this->anio = anio;
    }
    void setMes(int mes) {
        this->mes = mes;
    }
    void setDia(int dia) {
        this->dia = dia;
    }

    bool verificarLetras() {
        regex letras("([^a-zA-Z])+");
        return regex_match(this->fecha, letras);
    }
    void verificarFormato() {
        
        regex formato1("((([0-9]{1,2})||(0[0-9]))(/)(([0-9]{1,2}|(0[0-9])))(/)([0-9]{4}))+");
        regex formato2("((([0-9]{1,4}))(/)(([0-9]{1,2}|(0[0-9])))(/)([0-9]{1,2})||(0[0-9]))+");

        bool huh = regex_match(this->fecha, formato1);

        if (huh) {
            this->tipo = 1;
        }
        else if (regex_match(this->fecha, formato2)) {
            this->tipo = 2;
        }
        else this->tipo = 0;

    }
    void separarFecha() {
        size_t pos=0;
        string cpyfecha = this->getFecha();
        string substring;
        if (this->tipo == 1) {
            
            pos = cpyfecha.find('/');
            substring = cpyfecha.substr(0, pos);
            this->dia = stoi(substring);
            cpyfecha.erase(0, pos + 1);
            pos = cpyfecha.find('/');
            substring = cpyfecha.substr(0, pos);
            this->mes = stoi(substring);
            cpyfecha.erase(0, pos + 1);
            pos = cpyfecha.find('/');
            substring = cpyfecha.substr(0, pos);
            this->anio = stoi(substring);
            cpyfecha.erase(0, pos + 1);
                //12/12/1222
            
        }
        else if(this->tipo== 2){
            pos = cpyfecha.find('/');
            substring = cpyfecha.substr(0, pos);
            this->anio = stoi(substring);
            cpyfecha.erase(0, pos + 1);
            pos = cpyfecha.find('/');
            substring = cpyfecha.substr(0, pos);
            this->mes = stoi(substring);
            cpyfecha.erase(0, pos + 1);
            pos = cpyfecha.find('/');
            substring = cpyfecha.substr(0, pos);
            this->dia = stoi(substring);
            cpyfecha.erase(0, pos + 1);
            //1222/12/12
        }
    }
    bool verificarAnio() {
        if (this->anio > 0) {
            return true;
        }
        return false;
    }
    bool verificarMes() {
        if (this->mes > 0 && this->mes <= 12) {
            return true;
        }
        return false;
        
    }
    bool verificarDias(){
        int tipomes;//1.31d 2.30d 3.febrero
        


        if (this->mes == 1 || this->mes == 3 || this->mes == 5 || this->mes == 7 || this->mes == 8 || this->mes == 12) {
            tipomes = 1;
        }
        else if (this->mes == 4 || this->mes == 6 || this->mes == 9 || this->mes == 11) {
            tipomes = 2;
        }
        else tipomes = 3;


        switch(tipomes){
            case 1:
                if (this->dia <= 31 && this->dia > 0) return true;
            case 2:
                if (this->dia <= 30 && this->dia > 0) return true;
            case 3:
                if (this->anio % 4 == 0) {
                    if (this->anio % 100 == 0) {
                        if (this->anio % 400 == 0) {
                            if (this->dia <= 29 && this->dia > 0) {
                                return true;
                            }
                        }
                    
                    }
                }
                else {
                    if (this->dia <= 28 && this->dia > 0) {
                        return true;
                    }
                }
            default:
                return false;
        }
        
    }
    bool verificaciones() {
        if (verificarLetras()) {
            verificarFormato();
            separarFecha();
            if (verificarAnio()) {
                if (verificarMes()) {
                    if (verificarDias()) {
                        return true;

                    }
                }
            }
        }
        return false;
    }
};



int main()
{
    
    string str;
    while (str != "-") {
        cout << "Ingresa una fecha (DD/MM/AAAA o AAAA/MM/DD). \n Presiona '-' para salir"<<endl;
        cin >> str;
        date* fecha = new date(str);
        if (fecha->verificaciones()) {
            cout << "La fecha es valida" << endl;
        }
        else cout << "La fecha es invalida" << endl;
    }
        


    return 0;
}

