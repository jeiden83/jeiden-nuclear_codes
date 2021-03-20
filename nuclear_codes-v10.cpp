/*	Programa que permitirá al usuario añadir, modificar y borrar codigos nucleares de un .txt externo al programa mediante un menú de seleccion.	*/

//v0: Instrucciones listas.
//v0.1: Añadido el menu de seleccion.
//v0.2: Añadida la funcion para cargar los codigos a la memoria, y crear un nuevo fichero 
	//v0.25: Modo debugger
//v0.3: load_array(); funcionando correctamente, con codigos del tamaño fijo de 6
//v0.4: Añadida la funcion "add" al modify_size();
//v0.5: add(); funcionando correctamente	,	añadida la funcion display_array();		,	Modo debugger mejorado
//v0.6: Añadida la funcion display(); asi como para el menu.
//v0.7: Añadida y funcionando "modify();"
//v0.8: Añadido el "del"	,	añadida la funcion reorganize_array()	;	,	modo borrar al modify_size_array();
	//v0.85: funcionando como debe reorganize_array(); me tomó un rato descubrir el error de esta hdp 
//v0.9: Añadida y funcionando la funcion unload_array();
	//v0.95: bugfix[]
	//v0.99: all known bugs fixed[]	;	Añadida la funcion integer_check()	;	Añadida la funcion flo_to_int();
//v1.0:	Retoques a los comentarios, listo para la version final.
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
	
	//Variables para el buen uso
string *codes , aux_codes,aux_code, codes_raw;
int opcion, n_codes=0, i,j, debug_state = 0;	//if 1 then, pause on every step

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
int reorganize_array();			//Reordena el array dejando espacios vacios con # al final, y retorna un entero con la cantidad de espacios con buenos datos
void unload_array();			//Carga el array al .txt para finalizar con las operaciones
int integer_check(string);		//Revisa si una cadena tiene una cantidad de 6 digitos enteros, sin letras. Devuelve 1 si es así, 0 sino.
void flo_to_int(float&,int&);	//Funcion que intercambia el valor de un flotante a un entero


int main(){
	load_array();

		menu();	//Ta chikita

	unload_array();

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

	//Si solo en el archivo hay un espacio en blanco al cargarlo
	if((n_codes == 1)&&(aux_codes == "")){
		n_codes = 0;
	}

	debug(debug_state,2);	//show current n_codes

	//Luego se crea un array dinamico de strings para guardar esos codigos
	codes = new string[n_codes];
	
	//Se guardan los codigos a la memoria 
	for(i=0,j=0;j < n_codes;i+=6,j++){
		
		//Se substraen 6 de la cadena principal y se añaden al array dinamico
		*(codes+j) = codes_raw.substr(i,6);
	}

	//Se cierra el txt, pues solo se modificará el array
	file.close();
	
	debug(debug_state,1);	//show current loaded array
}
	//Mode == 1 to add, == 0 to del 
void modify_size_array(int mode,int amount){
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

	if(mode==0){

		//Declaramos nuevo array dinamico auxiliar, del tamaño final
		codes_aux = new string[n_codes - amount];

		//Copiamos data del array original al auxiliar
		for(i=0;i < (n_codes - amount);i++){
			*(codes_aux+i) = *(codes+i);
		}

		//Borramos array original y se crea de new con menos espacio
		delete[] codes;	codes = new string[n_codes - amount];

		//Copiamos data del array auxiliar al original v2
		for(i=0;i < (n_codes - amount);i++){
			*(codes+i) = *(codes_aux+i);
		}

		//Borramos array auxiliar para liberar la memoria
		delete[] codes_aux;

		//Disminuimos n_codes restandole el amount, pues es la variable que lleva el maximo del array
		n_codes -= amount;

		debug(debug_state,2);	//show current n_codes
	}
}
	//Comprueba si la cadena de digitos del strings son enteros
int integer_check(string aux_str){
	int value=0, aux_cad;

	//Se le suma 1				//Cadena a numeros			//De numeros a cadena						//Se le resta ese 1
	aux_str.insert(0,"1");		aux_cad = stoi(aux_str);	string aux_string = to_string(aux_cad);		aux_string.replace(0,1,"");	

	if((aux_string.length() == 6)) return value = 1;

	return value;
}
	//Añade al array una cantidad
void add_to_array(int amount){
	string digitos;

	cout<<"\n\n";
	fflush(stdin);

	for(i = (n_codes - amount),j=1;i < n_codes;i++,j++){
		
		do{
			cout<<"> ["<<j<<"]: Digite un codigo (6 digitos): "; getline(cin,aux_code);	*(codes+i) = aux_code;
			
			//Para verificar que la cantidad de digitos sea igual a 6, y de que sean todos digitos
		}while((integer_check(aux_code) == 0));
	}

	system("cls");
	cout<<"\n\n   Los digitos han sido guardados correctamente.\n\n";
	system("pause");

	debug(debug_state,1);	//show current loaded array
}
	//Organiza el array borrando los espacios vacios "#"
int reorganize_array(){
	string *aux_array;
	int aux_n_pos=0, delet=0;

	//Array dinamico auxiliar
	aux_array = new string[n_codes];

	//Revisamos el array para ordenarlo
	for(j=0;j < n_codes;j++){

			//Si la posicion en el array principal contiene un #, entonces no se copia
		if(*(codes + j) != "#"){

			*(aux_array + aux_n_pos) = *(codes + j);
			aux_n_pos++;
		}else delet++;
	}

	//Copiamos data del auxiliar al principal ya ordenado
	for(i=0;i < n_codes;i++){
		*(codes + i) = *(aux_array + i);

		//Los # al final
		if(i >= (n_codes - delet)){
			*(codes + i) = "#";
		}
	}

	//Chao dinamic aux
	delete[] aux_array;
	//Pal modify_size_array, pa saber cuantos espacio se va a quitar
	return delet;	//Espacios en el array desordenados
}
	//Carga el array al .txt
void unload_array(){
	ofstream file;

	//Si no hay digitos en el archivo, se borrara, de otra manera se abrirá
	if(n_codes == 0){

		remove("nuclear_codes.txt");
	}else file.open("nuclear_codes.txt",ios::out);

	//Copiando array al archivo dejando una linea por codigo
	for(int i=0;i < n_codes;i++){
		file<<*(codes+i);

		if(i < n_codes-1){
			file<<endl;
		}
	}
	file.close();
}	
	//Convierte un flotante a entero
void flo_to_int(float &aux_float,int &aux_int){
	aux_int = int(aux_float);
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
	int n_codes_add=0;
	float n_codes_add_f=0;

	system("cls");
	cout<<"\t\t--Modo Anyadir--\n\n",
	cout<<"\n";

	//Mientras se digite una cantidad mayor a cero
	do{
		cout<<"> Digite cuantos codigos anyadira: "; cin>>n_codes_add_f; 	flo_to_int(n_codes_add_f,n_codes_add);
	}while(n_codes_add < 1);
	

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
			
		//Para verificar que la cantidad de digitos sea igual a 6, y de que sean todos digitos
	}while((integer_check(aux_code) == 0));

	//Mostrando array y opcion de si seguir
	do{
		display(1,0);

		cout<<"\n> Seguir modificando? (1 = Si, 0 = No): "; cin>>mod_opcion;

		if(mod_opcion == 1) modify(); 
	}while(mod_opcion!=0);
}
void del(){
	float n_del_f;
	int n_del,mod_opcion, aux_pos, *pos_del;

	system("cls");
	cout<<"\t\t--Modo Borrar--\n\n";

	//Linea
	cout<<"\n";
	do{
		cout<<"> Digite cuantos codigos quiere borrar (max "<<n_codes<<"): "; cin>>n_del_f;	flo_to_int(n_del_f,n_del);
		//Mientras que sea la primera posicion y la ultima
	}while((n_del < 1)||(n_del > n_codes));
	fflush(stdin);

	//Mostrando array sin pausa
	display(0,0);

	//Nuevo array dinamico para las posiciones a borrar
	pos_del = new int[n_del];

	//Linea
	cout<<"\n";
	for(i=0;i < n_del;i++){

		do{
			cout<<"> ["<<i+1<<"] Digite la posicion del codigo: "; cin >> aux_pos; *(pos_del+i) = aux_pos-1;
			
			//Para verificar que la posicion digitada sea entre el min/max del array
		}while((aux_pos-1 < 0)||(aux_pos-1 >= n_codes));
	}

	//Remplazamos las posiciones del array principal con #, "borrar"
	for(i=0;i < n_del;i++){

		//Code en la posicion del valor añadido al vector dinamico
		*(codes + *(pos_del + i)) = "#";
	}
	debug(debug_state,1);

	//Reorganizamos array para dejar de ultimo las partes vacias, y borrar esas partes
	modify_size_array(0, reorganize_array() );	

	//Mostrando array y opcion de si seguir
	do{
		display(1,0);

		cout<<"\n> Seguir borrando? (1 = Si, 0 = No): "; cin>>mod_opcion;

		//Si se desea seguir borrando, pero no hay codigos
		if((mod_opcion == 1)&&(n_codes == 0)){
			cout<<"\n  No hay suficientes codigos.\n\n";	system("pause");
		}
		else if(mod_opcion == 1) del(); 
	}while(mod_opcion!=0);
}
void menu(){
	float opcion_f;

	do{
		system("cls");
		cout<<"\t\t--Menu de seleccion--\n\n",
		cout<<"\n  [1]: Anyadir codigo nuclear",
		cout<<"\n  [2]: Modificar codigo nuclear",
		cout<<"\n  [3]: Borrar codigo nuclear",
		cout<<"\n  [4]: Mostrar codigos nucleares",

		cout<<"\n\n  [0]: Salir y guardar",

		cout<<"\n\n> Digite una opcion: "; cin>>opcion_f;	flo_to_int(opcion_f,opcion);
		
		switch(opcion){
			case 1: add();	;break;
			case 2:{
				if(n_codes >= 1){	//Mientras haya al menos un codigo

					modify();break;
				}else cout<<"\n No hay suficientes codigos.\n";	system("pause");
			};break;
			case 3: {
				if(n_codes >= 1){	//Mientras haya al menos un codigo

					del()	;break;
				}else cout<<"\n No hay suficientes codigos.\n";	system("pause");
			};break;
			case 4: {
				if(n_codes >= 1){	//Mientras haya al menos un codigo

					display(1,1);break;
				}else cout<<"\n No hay suficientes codigos.\n";	system("pause");
			};
		}
	}while(opcion!=0);
}