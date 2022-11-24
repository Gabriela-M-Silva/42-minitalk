# 42-minitalk

Esse projeto trata da comunicação através de sinais (SIGUSR1 e SIGUSR2) <br> 
entre 2 programas. <br>

O server deve iniciar primeiro, imprimindo o PID e aguardando a mensagem <br>
do client. Em outro terminal, executamos o client com o PID e a msg a ser <br>
enviada. O server deve receber essa string e printar ela na tela. <br>

Para isso funcionar utilizando apenas 2 sinais, o client faz a conversão <br>
dessa string para binário, enviando bit a bit para o server, que reconstrói <br>
os bytes e monta a string novamente. <br>

Além disso, a cada bit enviado, o client entra em pause() e espera confirmação <br>
do server de que pode enviar o próximo. Esse tratamento garante que nenhum bit <br>
será perdido, evitando erros de transmissão. <br>
