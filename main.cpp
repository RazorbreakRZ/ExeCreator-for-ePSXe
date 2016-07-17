#include "File.h"

int main(int argc, char** argv) {
	if(argc>=2){
		for(int i=1;i<argc;i++){
			File f(argv[i],argv[0]);
			if(f.exists("ePSXe.exe")){
				f.createBAT();
				if(f.exists("BatToExe.exe")){
					f.createEXE();	
				}else{
					std::cout << "WARNING: No se ha localizado BatToExe.exe\n\nNo se ha podido crear el ejecutable pero si un .bat.\nPara convertirlo a .exe copia BatToExe.exe junto a este programa y reintentalo de nuevo.\n";
					system("pause>nul");
				}
			}else{
				system("ren pcsx2*.exe pcsx2.exe 2>nul");
				if(f.exists("pcsx2.exe")){
					f.createBAT2();
					if(f.exists("BatToExe.exe")){
						f.createEXE();	
					}else{
						std::cout << "WARNING: No se ha localizado BatToExe.exe\n\nNo se ha podido crear el ejecutable pero si un .bat.\nPara convertirlo a .exe copia BatToExe.exe junto a este programa y reintentalo de nuevo.\n";
						system("pause>nul");
					}
				}else{
					std::cout << "ERROR: No se ha localizado ePSXe.exe ni pcsx2.exe\n\n";
					std::cout << "Copia este ejecutable en la carpeta raiz del emulador y reintentalo de nuevo\n";
					system("pause>nul");
				}
			}	
		}		
	}else{
		std::cout << "Como usar: Arrastra al ejecutable uno o mas ficheros de imagen de juego.\n";
		system("pause>nul");
	}
	//system("pause>nul");
	return 0;
}

