// Eduarda dos Santos da Silva.
// Universidade Federal de Pelotas - Disciplina de Algoritmos e Estrutura de Dados I.
// Matricula: 22201985.

O código implementa uma agenda com lista duplamente ligada ordenada em que todas as variáveis temporárias e os estados da aplicação são armazenados em um único buffer de memória alocado dinamicamente. Os nós da lista são alocados separadamente na heap, mas o gerenciamento interno de memória segue as regras estabelecidas.

__Armazenamento sem variáveis explícitas:__
- Todas as variáveis temporárias estão armazenadas no buffer pBuffer.
- Acessos são feitos por deslocamentos (offsets) calculados dinamicamente com as macros.

__Lista Duplamente Ligada:__
- Facilita inserções ordenadas e remoções eficientes.
- O uso de ponteiros duplos (**) garante atualização correta da estrutura.

__Manutenção de Ordem Alfabética:__
- A função addPerson percorre a lista para encontrar a posição correta de inserção.

  __Principais Desafios__
  - Gestão manual de memória:
    - Todos os cálculos de posição dentro do buffer são feitos manualmente.
    - O buffer armazena dados de forma compacta, exigindo controle rigoroso para evitar acessos inválidos.
  - Ausência de structs:
    - Sem structs, é necessário organizar os dados de forma linear, simulando offsets como faria o compilador.
  - Usabilidade e limitações:
    - Ocódigo depende do tamanho fixo para os campos, como nome e e-mail.
   
  __Exemplo de fluxo:__
- Adicionar:
  - Insira "Ana, 25, ana@email.com".
  - Insira "Carlos, 30, carlos@email.com".
  - A lista agora é: Ana -> Carlos.
    
- Remover:
   - Remova "Ana".
   - A lista agora é: Carlos.

- Buscar:
   - Busque "Carlos".
   - Saída: "Carlos, 30, carlos@email.com".
  
- Listar:
   - Lista atual: "Carlos, 30, carlos@email.com".
