#include <windows.h>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>

#define TAM 200

int _tmain(int argc, TCHAR* argv[]) {
    HKEY chave;
    TCHAR chave_nome[TAM], par_nome[TAM], par_valor[TAM];
    TCHAR caminho[TAM];
    DWORD op, estado;
    BOOL continua = TRUE;
    LSTATUS res;

#ifdef UNICODE 
    _setmode(_fileno(stdin), _O_WTEXT);
    _setmode(_fileno(stdout), _O_WTEXT);
    _setmode(_fileno(stderr), _O_WTEXT);
#endif
    //pedir ao utilizador uma chave_nome("so2"
    //Acrescentar esta "chave_nome" ao "caminho"...
    //Chamar RegCreateKeyEX()...
    //Chamar RegCloseKey()...

    do {
        _tprintf_s(_T("Opção (1-Criar k, 2-..., 9-sair)?"));
        _tscanf_s(_T("%d"),&op);

        switch (op){
        case 1:
            _tcscpy_s(caminho, TAM, _T("Software\\aula\\"));
            _tprintf_s(_T("Nome da Key?"));
            _tscanf_s(_T("%s"), chave_nome,TAM);
            _tcscat_s(caminho, TAM, chave_nome);
            res = RegCreateKeyEx(HKEY_CURRENT_USER, caminho, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &chave, &estado);
            if (res == ERROR_SUCCESS) {
                if (estado == REG_OPENED_EXISTING_KEY)
                    _tprintf_s(_T("Abri a chave %s"), caminho);
            }
            break;
        case 2:
            //RegDelete
            _tcscpy_s(caminho, TAM, _T("Software\\aula\\"));
            _tprintf_s(_T("Nome da Key?"));
            _tscanf_s(_T("%s"), chave_nome, TAM);
            _tcscat_s(caminho, TAM, chave_nome);
            RegDeleteKeyEx(HKEY_CURRENT_USER, caminho, KEY_ALL_ACCESS, 0);
            break;
        case 3:
            //RegSetValueEx() define valor  necessario o nome e o valor
            if (chave != 0) {
                _tprintf_s(_T("Nome par ? "));
                _tscanf_s(_T("%s"), par_nome, TAM);
                _tprintf_S(_T("Valor PAr?"));
                _tscanf_s(_T("%s"), par_valor, TAM);
                res = RegSetValueEx(chave, par_nome, NULL, REG_SZ, (LPBYTE)par_valor, (_tcslen(par_valor) + 1) * sizeof(TCHAR));
            }
            

        case 4:
            //RegQueryValueEx(); necessario apenas o nome da variavel
            if (chave != 0) {
                _tprintf_s(_T("Nome par ? "));
                _tscanf_s(_T("%s"), par_nome, TAM);
                DWORD par_tipo, tam = sizof(par_valor);
                res = RegQueryValueEx(chave, par_nome, NULL, &par_tipo, (LPBYTE)par_valor, &tam);
                if(res == ERROR_SUCCESS)
                    _tprintf_s(_T("Par %s = %s (%d)"),par_nome, par_valor, par_tipo);
            }
            
        case 5:
            //RegDeleteValue(); pedir o nome e apagar o valor

           case 9:    
            continua = FALSE;
        default:
            break;
        }
    }while (continua);



    return 0;
}