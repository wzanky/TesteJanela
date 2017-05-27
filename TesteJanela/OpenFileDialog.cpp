#include <iostream>

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>

int main()
{
	FILE *arq;
	char texto_str[20];// <- teste de leitura do arquivo
	char filename[MAX_PATH];// Tamanho do direct�rio

	OPENFILENAME ofn;
	ZeroMemory(&filename, sizeof(filename));
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = "Text Files\0*.txt\0Any File\0*.*\0"; // Tipos de arquivos 
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = "Editor ";
	ofn.Flags = OFN_DONTADDTORECENT;
	ofn.lpstrInitialDir = ".";
	int cont;

	if (GetSaveFileNameA(&ofn))
	{
		std::string n = (std::string)filename;
		if (n.substr(n.length() - 4) != ".txt")
		{
			n += ".txt";
		}
		arq = fopen(n.c_str(), "w+");
		fprintf(arq, "CARALHO\nPORRA\0");
		fclose(arq);
	}
	if (GetOpenFileNameA(&ofn))
	{
		arq = fopen(filename, "r");
		/*char l[250];
		fscanf_s(arq, "%c", l);
		fclose(arq);
		std::cout << l << std::endl;*/
	}
	if (arq != NULL)
	{
		fseek(arq, 0, SEEK_END);
		cont = ftell(arq);
		fseek(arq, SEEK_END - 2, SEEK_SET);
	}
	while (fgets(texto_str, cont, arq) != NULL)
	{

		std::cout << texto_str << std::endl;
	}
	if (arq == NULL)
	{
		printf("Erro na abertura do arquivo!");
		return 1;
	}
	else
	{

		switch (CommDlgExtendedError())
		{
		case CDERR_DIALOGFAILURE: std::cout << "CDERR_DIALOGFAILURE\n";   break;
		case CDERR_FINDRESFAILURE: std::cout << "CDERR_FINDRESFAILURE\n";  break;
		case CDERR_INITIALIZATION: std::cout << "CDERR_INITIALIZATION\n";  break;
		case CDERR_LOADRESFAILURE: std::cout << "CDERR_LOADRESFAILURE\n";  break;
		case CDERR_LOADSTRFAILURE: std::cout << "CDERR_LOADSTRFAILURE\n";  break;
		case CDERR_LOCKRESFAILURE: std::cout << "CDERR_LOCKRESFAILURE\n";  break;
		case CDERR_MEMALLOCFAILURE: std::cout << "CDERR_MEMALLOCFAILURE\n"; break;
		case CDERR_MEMLOCKFAILURE: std::cout << "CDERR_MEMLOCKFAILURE\n";  break;
		case CDERR_NOHINSTANCE: std::cout << "CDERR_NOHINSTANCE\n";     break;
		case CDERR_NOHOOK: std::cout << "CDERR_NOHOOK\n";          break;
		case CDERR_NOTEMPLATE: std::cout << "CDERR_NOTEMPLATE\n";      break;
		case CDERR_STRUCTSIZE: std::cout << "CDERR_STRUCTSIZE\n";      break;
		case FNERR_BUFFERTOOSMALL: std::cout << "FNERR_BUFFERTOOSMALL\n";  break;
		case FNERR_INVALIDFILENAME: std::cout << "FNERR_INVALIDFILENAME\n"; break;
		case FNERR_SUBCLASSFAILURE: std::cout << "FNERR_SUBCLASSFAILURE\n"; break;
		default: std::cout << "You cancelled.\n";
		}
	}
	system("pause");
}