# **Shell em C**
Este é um simples shell implementado em linguagem C. Ele fornece uma interface de linha de comando para interagir com o sistema operacional.

### Como executar
1. **Compilação:** Compile o progrma usando um compilador C compatível, como o GCC
   
   ```
   gcc -o <nome_do_objeto> yshelldon.c
   ```
2. **Execução:** Com a compilação realizada corretamente, execute o programa da forma desejada

   a) Executando o próprio shell
   ```
   ./<nome_do_objeto>
   ```
   b) Executando um arquivo com uma lista de comandos
   ```
   ./<nome_do_objeto> <nome_do_arquiuvo_de_comandos>
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
   ls -la
   ```
   ```
   ls -a -l 
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
   cat <nome_do_arquivo_origem> > <nome_do_arquivo_destino>
   ```
   
- **Diretório atual**
  ```
  pwd
  ```
  
- **Saída**
  ```
  exit
  ```
