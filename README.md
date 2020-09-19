# Conversor de Coordenadas

![](https://github.com/diogo0001/geotag/blob/master/app_ui.PNG)

## Aplicação para verificação de coordenadas mapeadas

Aplicação desenvonvida em QT, onde o usuário pode abrir os dados de um arquivo *.txt.  
São mostrados os valores de altura máxima e mínima, e também a altura média.

O usuário pode converter as coordenadas para graus, minutos e segundos, com precisão de 4 casas nos segundos.
O arquivo pode ser salvo, tanto o convertido quanto o aberto. Também pode ser editado diretamente.
Para a conversão os dados devem estar com as coordenadas em latitude, logitude e altura, e ser aberto por arquivo.

## Features
  
    - Carrega os dados a partir de um arquivo: navegação em um dialog exibido pelo programa.
    - Converte para GMS: os dados que serão convertidos serão os abertos pelo arquivo.
    - Edição dos dados: pode-se editar os dados para salvá-los (dados da tela não são convertidos).
    - Salvar em arquivo: salva os dados em local desejado, navegação em um dialog exibido pelo programa.
    - Limpa os dados: limpa a tela e os dados armazenados.
    
## Dependências

  Aplicação desenvolvida no QT Creator 4.2, SDK QT 5.8.
  
## Implementações futuras

O aplicativo pode ser aprimorado, e algumas futuras implementações podem ser a conversão de GMS -> lat/longt, 
e também a conversão de dados inseridos diretamente na tela. 

