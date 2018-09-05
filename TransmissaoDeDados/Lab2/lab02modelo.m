% Transmiss�o de Dados
% Lab 01 - Modula��o AM
% Ricardo dos Santos - IF65F [EC35F|EL71C|IF65F]
% <>/09/2018

%% 1(a) Modulando AM-DSB 

clear;close all;clc %Limpeza 

%O arquivo audio.mat do moodle possui a vari�vel "m" salva com o �udio de 5 KHz. 
load audio 
%PS: Voc� pode salvar e carregar vari�veis em arquivos .mat com os comandos save
%e load:
m=m';          %transforma vetor coluna em vetor linha
fs=176400;     %freq de amostragem
% sound(m,fs)  %escute o �udio
N = length(m); %n�mero de amostras da vari�vel m




figure(1)


%% 1(b) Mesmas figuras com xlim
figure(2)




%% 1(c) - espectros de frequ�cias

% Crie o vetor de frequencias "f" de 0 a fs/1000 com N amostras. 
% Assim os valores de f v�o de 0 a 88.2 KHz. 
% Na hora de plotar, use xlabel('Frequ�ncia [kHz]').
% Fica melhor visualmente do que plotar o eixo x com frequencias de 0
% 88.2*10^3 em Hz, ao inv�s de kHz.



figure(3)


%% 1(d) -  Espectro de pot�ncias
[Pmm, fw] = pwelch(m,[],[],1024,fs);

 
figure(4)



%%
%%
%% 2(a) - demodula��o s�ncrona/coerente




%% filtro passa baixas

%Obtenha o filtro passa-baixas H:




V = fft(v)/N;             %fft de v(t) em valor complexo (sem o abs)
V2 = 2*V(1:N/2 +1);       %frequencias positivas apenas

V0 = V2.*H;               %Filtragem na frequ�ncia
%Retorna frequencias negativas ao fft para tirar fft inversa.
V0espelhado = [V0(1:end-1) V0(end-1:-1:1)];  
v0 = ifft(V0espelhado,'symmetric')*N;   %For�a o fft sim�trico

%sound(v0,fs)
%sound(m,fs)

%%
figure(5)


