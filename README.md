# LP-AED

S1 "the cat sleeps"
S2 "the dog runs"
S3 "a cat eats"

PASSO 1:

Cada palavra terá o seu token(id), incluindo espaços
| ID | Token
| 0 | "the"
| 1 | "a"
| 2 | " "
| 3 | "cat"
| 4 | "dog"
| 5 | "sleeps"
| 6 | "runs"
| 7 | "eats"

Passo 2: As frases iniciais em vez de serem palavras, virão os Ids
S1 [0, 2, 3, 2, 5]
S2 [0, 2, 4, 2, 6]
S3 [1, 2, 3, 2, 7]

Passo 3: Verifica quantas vezes a palavra/id aparece numa frase
| Token | ID | S1 | S2 | S3 |
| the | 0 | 1 | 1 | 0 |
| a | 1 | 0 | 0 | 1 |
| " " | 2 | 2 | 2 | 2 |
| cat | 3 | 1 | 0 | 1 |
| dog | 4 | 0 | 1 | 0 |
| sleeps | 5 | 1 | 0 | 0 |
| runs | 6 | 0 | 1 | 0 |
| eats | 7 | 0 | 0 | 1 |

Passo 4: dada uma nova frase, encontrar a frase do texto com maior similaridade.
Sin "the cat eats"
Tokenization da frase: [0, 2, 3, 2, 7]

Passo 5: verifica o quão similar uma frase é a outra 
S1: "the cat sleeps" ~0,86 Elevada
S3: "a cat eats" ~0,86 Elevada
S2: "the dog runs" ~0,71 Média
