![QWIRKLE](https://i.ibb.co/3BrbhW9/image.png)

# Qwirkle, um projeto de jogo da SSC601	— 2020
Uma versão em C do jogo de tabuleiro norte americano Qwirkle. Criado como parte do último projeto da disciplina SSC601, Laboratório de Introdução à Ciência da Computação I, da Universidade de São Paulo – Campus São Carlos. Curso de Engenharia da Computação, turma 020. Professor Adenilso da Silva Simão.

> Membros do grupo em ordem de pontuação: Rafael Dalonso Schultz (11800945) e Ricardo Monteiro Barbosa (11800604).

[![License](http://img.shields.io/:license-mit-blue.svg?style=flat-square)](http://badges.mit-license.org) [![Matéria](https://img.shields.io/badge/mat%C3%A9ria-SSC601-brightgreen)](https://github.com/badges/badgerbadgerbadger) [![Universidade](https://img.shields.io/badge/universidade-USP-orange)](https://github.com/badges/badgerbadgerbadger)


![Jogo](http://g.recordit.co/0z9DpVGPIa.gif)

---

## Tabela de conteúdos

- [Jogabilidade](#jogabilidade)
- [Arquivos](#arquivos)
- [Grupo](#grupo)
- [Licença](#licença)

---

## Jogabilidade

O funcionamento do programa segue a proposta do jogo norte americano, mas com algumas adaptações para simplificar a jogabilidade. No início do jogo, por exemplo, ao contrário do original, em que o primeiro jogador é aquele que possui maior linha inicial (e, no caso de todos terem o mesmo tamanho de linha, começa o jogador mais velho), o jogo em C é iniciado pelo jogador número 0, ou seja, o primeiro a escrever seu nome.

![Inicio](https://i.ibb.co/tB5xQWm/image.png)

O usuário preenche, então, o número de jogadores e seus nomes, pelos quais serão identificados em cada jogada, além de optar ou não pelo cheat mode (“modo trapaça”). Assim que preenchidos, é mostrado o tabuleiro inicial – de linha 0 e coluna 0, com espaço para alocar a primeira peça –, as peças de cada jogador e as opções para o jogador número 0. O jogador escolhe uma das opções.

![Opcoes](https://i.ibb.co/3CgytRB/image.png)

A pontuação e a dinâmica do jogo foram feitas conforme as regras do original. A ordem da jogada individual segue a alocação de peças, pontuação da jogada e retirada de peças da “sacola” para manter 6 peças em mão. Não se pode alocar fichas individuais, todas devem estar “coladas”, isto é, formando filas entre si.

Além disso, tal como o original, o programa permite colocar múltiplas filas na vez do jogador, desde que tenham a mesma cor ou forma e mesma linha (tocam-se), e esse jogador é pontuado somando os valores unitários das peças existentes na fila mais a peça que colocou. Por fim, caso seja detectado um QWIRKLE!, isto é, o preenchimento completo de uma fila com seis cores ou letras, o usuário responsável por completar recebe um bônus de seis pontos.

![Qwirkle](https://i.ibb.co/j5WLxn0/Vanilla-0-4s-289px-2.gif)

O jogo continua até não houver mais blocos na bolsa. Então, continua até um dos jogadores não possuir mais nenhuma ficha em sua mão. Esse jogador recebe, também, um bônus de seis pontos. Finalmente, são verificadas as pontuações, e vence o jogador que mais pontuou.

---

### Arquivos
A codificação do jogo se deu de forma organizada, por meio de diversos arquivos que ajudaram a estruturar o problema.

- /headers
> Pasta que possui os arquivos .h, cabeçalhos que organizam informações para cada um dos arquivos do programa

- main.c
> Arquivo que contém a função principal, responsável por chamar as funções essenciais ao bom funcionamento do programa

- output.c
> Arquivo que contém as funções que interagem com o jogador

- blocks.c
> Arquivo que contém as funções que lidam com as peças – tanto na sacola, quanto na mão do jogador

- board.c
> Arquivo que descreve o tabuleiro do jogo

- buffer.c
> Arquivo que lida com a memória temporária do programa

- colors.c
> Arquivo com os códigos de cores (representadas também por números)

- game.c
> Arquivo que lida com a jogabilidade em si. Possui funções de rodadas dos jogadores e de verificação

- players.c
> Arquivo que lida com os jogadores, partindo de sua definição (quantidade, nome) 

- pontuacao.c
> Arquivo que lida com a pontuação dos jogadores, analisando eixos horizontais e verticais e buscando por QWIRKLES!


---

### Grupo
> Membros do grupo em ordem de pontuação:
- Rafael Dalonso Schultz (11800945)
- Ricardo Monteiro Barbosa (11800604)

## Licença

[![License](http://img.shields.io/:license-mit-blue.svg?style=flat-square)](http://badges.mit-license.org)

- **[Licença MIT](http://opensource.org/licenses/mit-license.php)**
