/*	Programa que permitirá al usuario añadir, modificar y borrar codigos nucleares de un .txt externo al programa mediante un menú de seleccion.	*/
//v0: Instrucciones listas.
//v0.1: Añadido el menu de seleccion.
//v0.2: Añadida la funcion para cargar los codigos a la memoria, y crear un nuevo fichero 
	//v0.25: Modo debugger
//v0.3: load_array(); funcionando correctamente, con codigos del tamaño fijo de 6
//v0.4: Añadida la funcion "add" al modify_size();
//v0.5: add(); funcionando correctamente	,	añadida la funcion display_array();		,	Modo debugger mejorado
//v0.6: Añadida la funcion display(); asi como para el menu.
//v0.7:
#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
using namespace std;
	
	//Variables para el buen uso
string *codes;
string aux_codes,aux_code;
string codes_raw;
int opcion;
int n_codes=0,n_codes_add=0;
int i,j;
int debug_state=1;	//if 1 then, pause on every step

	//Menus de seleccion
void add();						//Añadir un codigo
void modify();					//Modificar un codigo
void del();						//Borrar un codigo
void display(int,int);			//Muestra el array entero	;	("1==system("cls")","1==system("pause")")
void menu();			//Englobado
	//Funciones
void new_file();				//Nuevo fichero
void debug(int,int);			//Modo debug, para saber como van las cosas por pasos	;	("state","0==just pause,1==cout array,2==cout==n_codes")
void load_array();				//Carga el array a la memoria
void modify_size_array(int,int);//Modifica el tamaño del array; ("modo 1==add,0==del","cantidad")
void add_to_array(int);			//Añade x cantidad al array al final de este


int main(){
	load_array();

		menu();

	cout<<"\ngrasias por su atencion\n";
	system("pause");
	return 0;
}

//Modo debugger necesario para saber si las cosas van bien en algunas partes
void debug(int debug_state,int mode){
	if(debug_state==1){

		switch(mode){
			//show current loaded array == 1;
			case 1:{
				cout<<"\n";
				for(i=0; i < n_codes;i++){
					cout<<*(codes+i)<<endl;
				}
				cout<<"\n";
			};	break;
			//show current n_codes == 2;
			case 2:{
				if(debug_state==1) cout<<"\n   "<<n_codes<<" codes\n";
			};
		}
		system("pause");
	}
}

//Funcion usada para crear un nuevo archivo
void new_file(){
	ofstream file;

	//Creando archivo
	file.open("nuclear_codes.txt",ios::out);

	//En caso de que falle crearlo
	if(file.fail()){
		cout<<"No se pudo crear el archivo\n";
		system("pause");
		exit(1);
	}
	//De otro modo
	cout<<"\nArchivo creado correctamente\n";

	//Cerramos el archivo, ya que solo se necesita crearlo
	file.close();
}

//Funcion usada para cargar los codigos del .txt hacia un array de strings, para posterior uso
void load_array(){
	string aux;
	fstream file;

	//Se abre el archivo para la lectura
	file.open("nuclear_codes.txt",ios::in);

	//Si el archivo falla en abrir, se crea uno y se vuelve a abrir
	if(file.fail()){
		cout<<"No se pudo abrir el archivo",
		cout<<"\nCreando uno nuevo...\n";
		new_file();
		
		file.open("nuclear_codes.txt",ios::in);

		//Si el archivo falla en abrir de new xd
		if(file.fail()){
			cout<<"No se pudo abrir el archivo.",
			system("pause");
			exit(1);
		}
		debug(debug_state,0);
	}

	//Primero se revisa cuantos codigos ya hay en el archivo, y luego se añade a una cadena entera, 
	for(i=0;!file.eof();i++){
		//Copia al auxiliar
		getline(file,aux_codes);
		//Añade del auxiliar a la cadena entera
		codes_raw += aux_codes;
		//Añade uno al contador de codigos
		n_codes++;
	}

	debug(debug_state,2);	//show current n_codes

	//Luego se crea un array dinamico de strings para guardar esos codigos
	codes = new string[n_codes];
	
	//Se guardan los codigos a la memoria 
	for(i=0,j=0;j < n_codes;i+=6,j++){
		
		//Se substraen 6 de la cadena principal y se añaden al array dinamico
		*(codes+j) = codes_raw.substr(i,6);
	}

	debug(debug_state,1);	//show current loaded array
}
void modify_size_array(int mode,int amount){	//mode == 1, == 0 to del, 
	string *codes_aux;

	//Modo anyadir
	if(mode==1){

		//Declaramos nuevo array dinamico auxiliar
		codes_aux = new string[n_codes];

		//Copiamos data del array original al auxiliar
		for(i=0;i < n_codes;i++){
			*(codes_aux+i) = *(codes+i);
		}

		//Borramos array original y se crea de new con mas espacio
		delete[] codes;	codes = new string[n_codes + amount];

		//Copiamos data del array auxiliar al original v2
		for(i=0;i < n_codes;i++){
			*(codes+i) = *(codes_aux+i);
		}

		//Borramos array auxiliar para liberar la memoria
		delete[] codes_aux;

		//Aumentamos n_codes sumandole el amount, pues es la variable que lleva el maximo del array
		n_codes += amount;

		debug(debug_state,2);	//show current n_codes
	}
}
void add_to_array(int amount){
	string digitos;

	cout<<"\n\n";
	fflush(stdin);

	for(i = (n_codes - amount),j=1;i < n_codes;i++,j++){
		
		do{
			cout<<"  "<<j<<". Digite un codigo (6 digitos): "; getline(cin,aux_code);	*(codes+i) = aux_code;
			
			//Para verificar que la cantidad de digitos sea igual a 6
		}while(aux_code.length()!=6);
	}

	system("cls");
	cout<<"\n\n   Los digitos han sido guardados correctamente.\n\n";
	system("pause");

	debug(debug_state,1);	//show current loaded array
}

void display(int clean,int pause){
	//Limpiar si clean == 1, para en modo menu, sino en funcion
	if(clean == 1){
		system("cls");
		cout<<"\t\t--Mostrando codigos--\n\n";

	}else cout<<"\n\n\t\t--Mostrando codigos--\n\n";

	for(i=0; i < n_codes;i++){

		cout<<"["<<i+1<<"]: "<<*(codes+i)<<endl;
	}
	cout<<"\n";

	//Pausar si pause == 1;
	if(pause == 1) system("pause");
}

void add(){
	system("cls");
	cout<<"\t\t--Modo Anyadir--\n\n",
	cout<<"\n   Digite cuantos codigos anyadira: "; cin>>n_codes_add;

	//Modificamos el tamanyo del array, para los nuevos codigos
	modify_size_array(1,n_codes_add);

	//Anyadimos al final del array (n_codes - n_codes_add)
	add_to_array(n_codes_add);

	//Mostrando resultado
	display(0,1);
}
void modify(){
	int code_pos,mod_opcion;

	system("cls");
	cout<<"\t\t--Modo Modificar--";

	//Mostrando array sin pausa
	display(0,0);

	//Linea
	cout<<"\n";
	do{
		cout<<"> Digite la posicion del codigo (1,"<<n_codes<<"): "; cin>>code_pos;
		//Mientras que sea la primera posicion y la ultima
	}while((code_pos < 1)||(code_pos > n_codes));
	fflush(stdin);

	//Linea
	cout<<"\n";
	do{
		cout<<"> Digite el codigo (6 digitos): "; getline(cin,aux_code);	*(codes + code_pos-1) = aux_code;
			
		//Para verificar que la cantidad de digitos sea igual a 6
	}while(aux_code.length()!=6);

	//Mostrando array y opcion de si seguir
	do{
		display(1,0);

		cout<<"\n> Seguir modificando? (1 = Si, 0 = No): "; cin>>mod_opcion;

		if(mod_opcion == 1) modify(); 
	}while(mod_opcion!=0);
}

void del(){

}

void menu(){
	do{
		system("cls");
		cout<<"\t\t--Menu de seleccion--\n\n",
		cout<<"\n  [1]: Anyadir codigo nuclear",
		cout<<"\n  [2]: Modificar codigo nuclear",
		cout<<"\n  [3]: Borrar codigo nuclear",
		cout<<"\n  [4]: Mostrar codigos nucleares",

		cout<<"\n\n  [0]: Salir",

		cout<<"\n\n> Digite una opcion: "; cin>>opcion;
		
		switch(opcion){
			case 1: add();		;break;
			case 2: modify();	;break;
			case 3: del();		;break;
			case 4: display(1,1);;
		}
	}while(opcion!=0);
}