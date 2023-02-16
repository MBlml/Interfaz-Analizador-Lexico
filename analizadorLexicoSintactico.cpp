#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

using namespace std;

//Verificar si es un puntuador
bool esPuntuador(char caracter)
{
    if (caracter == ' ' || caracter == '+' || caracter == '-' || caracter == '*' ||
        caracter == '/' || caracter == ',' || caracter == ';' || caracter == '>' ||
        caracter == '<' || caracter == '=' || caracter == '(' || caracter == ')' ||
        caracter == '[' || caracter == ']' || caracter == '{' || caracter == '}' ||
        caracter == '&' || caracter == '|')
    {
        return true;
    }
    return false;
}

//Verificar si es un identificador
bool identificadorValido(char* str)						
{
    if (str[0] == '0' || str[0] == '1' || str[0] == '2' ||
        str[0] == '3' || str[0] == '4' || str[0] == '5' ||
        str[0] == '6' || str[0] == '7' || str[0] == '8' ||
        str[0] == '9' || esPuntuador(str[0]) == true)
    {
        return false;
    }
    //no es válido si el primer carácter de la cadena es un dígito o un carácter especial					
    int i, len = strlen(str);
    if (len == 1)
    {
        return true;
    }
    //es verdadero si la longitud es uno, la validación ya está completa
    else
    {
        //el identificador no puede contener caracteres especiales
        for (i = 1; i < len; i++)						
        {
            if (esPuntuador(str[i]) == true)
            {
                return false;
            }
        }
    }
    return true;
}

//verificar si el caracter dado es un operador
bool esOperador(char caracter)							
{
    if (caracter == '+' || caracter == '-' || caracter == '*' ||
        caracter == '/' || caracter == '>' || caracter == '<' ||
        caracter == '=' || caracter == '|' || caracter == '&')
    {
        return true;
    }
    return false;
}

//verificar si la subcadena dada es una palabra clave
bool esPalabraClave(char* str)						
{
    if (!strcmp(str, "if") || !strcmp(str, "else") ||
        !strcmp(str, "while") || !strcmp(str, "do") ||
        !strcmp(str, "break") || !strcmp(str, "continue")
        || !strcmp(str, "int") || !strcmp(str, "double")
        || !strcmp(str, "float") || !strcmp(str, "return")
        || !strcmp(str, "char") || !strcmp(str, "case")
        || !strcmp(str, "long") || !strcmp(str, "short")
        || !strcmp(str, "typedef") || !strcmp(str, "switch")
        || !strcmp(str, "unsigned") || !strcmp(str, "void")
        || !strcmp(str, "static") || !strcmp(str, "struct")
        || !strcmp(str, "sizeof") || !strcmp(str, "long")
        || !strcmp(str, "volatile") || !strcmp(str, "typedef")
        || !strcmp(str, "enum") || !strcmp(str, "const")
        || !strcmp(str, "union") || !strcmp(str, "extern")
        || !strcmp(str, "bool") || !strcmp(str, "cout") 
        || !strcmp(str, "str"))
    {
        return true;
    }
    else
    {
        return false;
    }
}

//verificar si la subcadena dada es un número
bool esNumero(char* str)							
{
    int i, len = strlen(str), numOfDecimal = 0;
    if (len == 0)
    {
        return false;
    }
    for (i = 0; i < len; i++)
    {
        if (numOfDecimal > 1 && str[i] == '.')
        {
            return false;
        }
        else if (numOfDecimal <= 1)
        {
            numOfDecimal++;
        }
        if (str[i] != '0' && str[i] != '1' && str[i] != '2'
            && str[i] != '3' && str[i] != '4' && str[i] != '5'
            && str[i] != '6' && str[i] != '7' && str[i] != '8'
            && str[i] != '9' || (str[i] == '-' && i > 0))
        {
            return false;
        }
    }
    return true;
}

//extraer la subcadena requerida de la cadena principal
char* subCadena(char* realStr, int l, int r)				
{
    int i;

    char* str = (char*)malloc(sizeof(char) * (r - l + 2));

    for (i = l; i <= r; i++)
    {
        str[i - l] = realStr[i];
        str[r - l + 1] = '\0';
    }
    return str;
}

//analizar la expresión
void analizar(char* str)						
{
    int left = 0, right = 0;
    int len = strlen(str);
    bool puntuador = false, operador = false;
    while (right <= len && left <= right) {
        //si el carácter es un dígito o un caracter
        if (esPuntuador(str[right]) == false)			
        {
            right++;
        }
        //si el carácter es un marcador
        if (esPuntuador(str[right]) == true && left == right)		
        {
            puntuador = true;
            if (esOperador(str[right]) == true)
            {
                operador = true;
            }
            else {
                operador = false;
            }
        
            if (puntuador == true && operador == true) {
                std::cout << '"' << str[right] <<'"' << " = Puntuador y Operador\n";
            }
            else if (puntuador == true && operador == false){
                std::cout << '"' << str[right] <<'"' << " = Puntuador\n";
            }
            else if (operador == true && puntuador == false){
                std::cout << '"' << str[right] <<'"' << " = Operador\n";
            }
            right++;
            left = right;
        }

        //comprobar si la subcadena analizada es una palabra clave, un identificador o un número
        else if (esPuntuador(str[right]) == true && left != right
            || (right == len && left != right)) 			
        {
            //extraer subcadena
            char* sub = subCadena(str, left, right - 1);   

            if (esPalabraClave(sub) == true)
            {
                cout << '"' << sub << '"' << " = Palabra clave\n";
            }
            else if (esNumero(sub) == true)
            {
                cout << '"' << sub << '"' << " = Numero\n";
            }
            else if (identificadorValido(sub) == true
                && esPuntuador(str[right - 1]) == false)
            {
                cout << '"' << sub << '"' << " = Identificador valido\n";
            }
            else if (identificadorValido(sub) == false
                && esPuntuador(str[right - 1]) == false)
            {
                cout << '"' << sub << '"' << " = Identificador no valido\n";
            }

            left = right;
        }
    }
    return;
}

class AnalizadorSintactico {
public:
    AnalizadorSintactico(string expresion) : m_expresion(expresion) {}

    bool analizar() {
        m_pos = 0;
        m_exito = true;
        expr();
        return m_exito && m_pos == m_expresion.length();
    }

private:
    string m_expresion;
    int m_pos;
    bool m_exito;

    void expr() {
        term();
        while (m_exito && (m_expresion[m_pos] == '+' || m_expresion[m_pos] == '-' || m_expresion[m_pos] == '*' || m_expresion[m_pos] == '/')) {
            m_pos++;
            term();
        }
    }

    void term() {
        if (isdigit(m_expresion[m_pos])) {
            numero();
        } else if (m_expresion[m_pos] == '(') {
            m_pos++;
            expr();
            if (m_expresion[m_pos] == ')') {
                m_pos++;
            } else {
                m_exito = false;
            }
        } else {
            m_exito = false;
        }
    }

    void numero() {
        int inicio_pos = m_pos;
        while (m_pos < m_expresion.length() && isdigit(m_expresion[m_pos])) {
            m_pos++;
        }
        if (inicio_pos == m_pos) {
            m_exito = false;
        }
    }
};



void analizadorLexico() {
    char codigo[100];

    cout << "-ANALIZADOR LEXICO-\n\n";
    cout << "Linea a analizar: ";
    cin.ignore();
    cin.getline(codigo, 100,'\n'); //cout << 1+2 abc +}

    cout << "\n\n";

    analizar(codigo);

    cout << "\n\n";
}

void analizadorSintactico() {
    string expresion;
    cout << "-Analizador Sintactico-\n(Solo sumas y restas)\n\n";
    cout << "Linea a analizar: ";
    cin.ignore();
    cin >> expresion;

    AnalizadorSintactico analizador(expresion);
    if (analizador.analizar()) {
        cout << expresion << " = Valida" << endl << endl;
    } else {
        cout << expresion << " =  No valida" << endl << endl;
    }
}

int main() {
    int opc = 1;

    while (opc != 0) {
        cout << "-Analizadores de codigo-\n";
        cout << "1) Analizador Lexico\n";
        cout << "2) Analizador Sintactico\n";
        cout << "0) Salir\n";
        cout << "Usuario: ";
        cin >> opc; 

        switch (opc) {
        case 1:
            analizadorLexico();
            break;
        case 2:
            analizadorSintactico();
            break;
        case 0: 
            cout << "Hasta luego\n";
            break;
        default: 
            cout << "Opcion no valida\n";
            break;
        }
    }
    
    return 0;
}
