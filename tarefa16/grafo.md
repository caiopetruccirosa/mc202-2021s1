# Modelagem do Problema Usando Grafo

## Estrutura do Grafo

Para esse problema, podemos representar as celas e suas ligações/passagens como um grafo.

Nesse grafo, os vértices são as próprias celas e uma aresta, que conecta dois vértices, 
representa a possibilidade de ir de uma cela para a outra, em apenas uma rodada.

Considerando as regras que envolvem os atributos dos personagens, como o fato de que
cada personagem possui os atributos mínimos da cela em que está no início da rodada e 
que pode incrementar apenas em um ponto uma de suas habilidades em cada rodada, a 
existência de uma aresta entre dois vértices se dá pela diferença de apenas um ponto de
habilidade faltante entre duas celas para que os atributos mínimos de uma satisfação os 
atributos mínimos da outra.

Por exemplo, para as celas cuja entrada sejam:
```
corredor            3 4 5 3 5 1
galpao-misterioso   3 4 5 4 5 2
quarto-dos-brutos   3 4 4 3 5 2
```

Sabemos que é possível ir da `corredor` para `quarto-dos-brutos` e vice-versa, mas não
da `corredor` para a `galpao-misterioso`.

## Saída

A saída desse problema, pensando que o problema foi modelado como um grafo, se trata
basicamente de uma listagem de todos os vértices (celas), cuja a distância até todas 
as celas em que os jogadores estão no início do jogo seja menor ou igual a 2.

Isso se dá pois, todos os jogadores querem se encontrar na mesma cela após 2 rodadas, e 
isso só será possível se a cela de encontro (ponto de encontro) terá distância menor ou 
igual a 2 às celas iniciais dos jogadores.