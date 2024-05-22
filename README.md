# YSHELLDON ⚡

Este é um simples shell implementado em linguagem C. Ele fornece uma interface de linha de comando para interagir com o sistema operacional.

### Instalação
1. **Navegue até um diretório**
    ```
    cd <nome_do_diretório>
    ```
    
2. **Clone o repositório**
    ```
    git clone https://github.com/RafaMazoliniF/yShelldon.git
    ```
    
### Execução
1. **Compilação:** Compile o programa usando um compilador C compatível, como o GCC
   
   ```
   gcc -o yshelldon yshelldon.c
   ```
2. **Execução:** Com a compilação realizada corretamente, execute o programa da forma desejada

   a) Executando o próprio shell
   ```
   ./yshelldon
   ```
   b) Executando um arquivo com uma lista de comandos
   ```
   ./yshelldon <nome_do_arquivo_de_comandos.formato>
   ```
   
### Comandos suportados
Este shell suporta os comandos:
- **Entrada em um diretório**
  
   a) Diretório absoluto
   ```
   cd <caminho_completo_do_diretorio>
   ```
   b) Diretório relativo
   ```
   cd <nome_do_diretorio>
   ```
   
- **Listagem diretórios e arquivos**

   a) Diretórios e arquivos não ocultos
   ```bash
   ls
   ```
   b) Todos diretórios e arquivos
   ```
   ls -a
   ```
   c) Informações dos diretórios e arquivos não ocultos
   ```
   ls -l
   ```
   d) Informações de todos os diretorios e arquivos
   ```
   ls -al
   ```
   ```
   ls -a -l
   ```
   ```
   ls -la 
   ```
   ```
   ls -l -a
   ```
   
- **Manipulação de conteúdo de arquivos**

  a) Impressão na tela
   ```
   cat <nome_do_arquivo>
   ```
   b) Cópia do conteúdo para outro arquivo
   ```
   cat <nome_do_arquivo_origem.formato> > <nome_do_arquivo_destino.formato>
   ```
   
- **Manipulação do PATH**

  a) Impressão na tela
  ```
  $PATH
  ```
  b) Adição de diretórios
  ```
  $PATH -add <diretório>
  ```
  c) Remoção do último diretório
  ```
  $PATH -rm 
  ```
  
- **Diretório atual**
  ```
  pwd
  ```

- **Limpeza de tela**
  ```
  clear
  ```
  
- **Saída**
  ```
  exit
  ```
