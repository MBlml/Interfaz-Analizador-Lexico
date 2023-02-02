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

int main()
{
    char codigo[100];

    cout << "-ANALIZADOR LEXICO-\n\n";
    cout << "Linea a analizar: ";
    cin.getline(codigo, 100,'\n'); //cout << 1+2 abc +}

    cout << "\n\n";

    analizar(codigo);

    cout << "\n\n";
    return 0;
}