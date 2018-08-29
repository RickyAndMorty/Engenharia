clear all
close all
clc
%a
t = (0:999)*0.05;

g = cos(pi.*t) + 2*cos(4*pi.*t) - 3*sin(6*pi.*t);


%b
subplot(2,1,1);

plot(t,g)
title('estou aqui')
xlabel('tempo(s)')
ylabel('Amplitude(V)')
aux = subplot(2,1,2);

plot(t(1,1:101),g(1,1:101),'o--')
title('estou aqui again')
xlim(aux,[0 5])
xlabel('tempo(s)')
ylabel('Amplitude(V)')

%c1
% T = 2 segundos
% N�mero de amostras = 40

Nt = 40;

EgT = sum(abs(g(1:Nt).^2).*0.05)

%c1) Calcule a a pot�ncia m�dia (Pg) de todo o sinal, considerando To a dura�c�ao de todo o sinal em segundos,
%sendo
T0 = 50;% Dura��o de todo o sinal em segundos
N = 1000;%N�mero de amostras
Pg = (1/T0)* sum(abs(g(1:N).^2).*0.05)

%





