%% Laboratório 03 - Modulação em amplitude


%% 1-a

clc
clear all
load audio

m1 = m1';            %Transforma o vetor coluna em vetor linha
m2 = m2';
fs = 176400;         %Frequência de amostragem
ts = 1/fs;           %Período de amostragem
N = length(m1);      %Número de amostras da variável m1 = m2
t = (0:N-1)*ts;      %Tempo
fc = 12000;          %Frequência da portadora (carrier)
c1 = cos(2*pi*fc*t); %Carrier 1
c2 = sin(2*pi*fc*t); %Carrier 2
s1 = m1.*c1;         %Sinal modulado em AM-DSB
s2 = m2.*c2;


figure(1)
subplot(3,1,1)
plot(t,m1)
grid on
title('Sinal m1(t)')
xlabel('Tempo [s]')
ylabel('Amplitude [V]')
xlim([0.7 0.72])

figure(2)
subplot(3,1,1)
plot(t,m2)
grid on
title('Sinal m2(t)')
xlabel('Tempo [s]')
ylabel('Amplitude [V]')
xlim([0.7 0.72])

figure(1)
subplot(3,1,2)
plot(t,c1)
grid on
title('Portadora c1(t)')
xlabel('Tempo [s]')
ylabel('Amplitude [V]')
xlim([0.7 0.72])

figure(2)
subplot(3,1,2)
plot(t,c2)
grid on
title('Portadora c2(t)')
xlabel('Tempo [s]')
ylabel('Amplitude [V]')
xlim([0.7 0.72])

figure(1)
subplot(3,1,3)
plot(t,s1)
hold on
plot(t,m1)
grid on
title('Sinais s1(t) e m1(t)')
xlabel('Tempo [s]')
ylabel('Amplitude [V]')
xlim([0.7 0.72])

figure(2)
subplot(3,1,3)
plot(t,s2)
hold on
plot(t,m2)
grid on
title('Sinais s2(t) e m2(t)')
xlabel('Tempo [s]')
ylabel('Amplitude [V]')
xlim([0.7 0.72])

%% 1-c

f = linspace(0,(fs/2000),N/2+1);

figure(3)
M1 = fft(m1);
M1_abs = abs(2*M1(1:(N/2+1))/N);
subplot(3,1,1)
plot(f,M1_abs)
title('FFT m1(t)')
xlabel('Frequência [kHz]')
ylabel('|M1(f)|')
xlim([0 18])

figure(4)
M2 = fft(m2);
M2_abs = abs(2*M2(1:(N/2+1))/N);
subplot(3,1,1)
plot(f,M2_abs)
title('FFT m2(t)')
xlabel('Frequência [kHz]')
ylabel('|M2(f)|')
xlim([0 18])

figure(3)
C1 = fft(c1);
C1_abs = abs(2*C1(1:(N/2+1))/N);
subplot(3,1,2)
plot(f,C1_abs)
title('FFT c1(t)')
xlabel('Frequência [kHz]')
ylabel('|C1(f)|')
xlim([0 18])

figure(4)
C2 = fft(c2);
C2_abs = abs(2*C2(1:(N/2+1))/N);
subplot(3,1,2)
plot(f,C2_abs)
title('FFT c2(t)')
xlabel('Frequência [kHz]')
ylabel('|C2(f)|')
xlim([0 18])

figure(3)
S1 = fft(s1);
S1_abs = abs(2*S1(1:(N/2+1))/N);
subplot(3,1,3)
plot(f,S1_abs)
title('FFT s1(t)')
xlabel('Frequência [kHz]')
ylabel('|S1(f)|')
xlim([0 18])

figure(4)
S2 = fft(s2);
S2_abs = abs(2*S2(1:(N/2+1))/N);
subplot(3,1,3)
plot(f,S2_abs)
title('FFT s2(t)')
xlabel('Frequência [kHz]')
ylabel('|S2(f)|')
xlim([0 18])

%% 1-d

figure(5)

s = s1 + s2;

subplot(3,1,1)
plot(t,s1)
grid on
title('Sinal modulado s1(t)')
xlabel('Tempo [s]')
ylabel('Amplitude [V]')
xlim([2.2 2.201])

subplot(3,1,2)
plot(t,s2)
grid on
title('Sinal modulado s2(t)')
xlabel('Tempo [s]')
ylabel('Amplitude [V]')
xlim([2.2 2.201])

subplot(3,1,3)
plot(t,s)
grid on
title('Sinal modulado QAM s(t)')
xlabel('Tempo [s]')
ylabel('Amplitude [V]')
xlim([2.2 2.201])

%% Exercício 2-a

v1 = s.*cos(2*pi*fc*t);
v2 = s.*sin(2*pi*fc*t);

%% Exercício 2-b

V1 = fft(v1);                        %fft de v1(t) em valor complexo (sem o abs)
V1_abs = abs(2*V1(1:(N/2+1))/N);     %módulo de V1(f)

V2 = fft(v2);
V2_abs = abs(2*V2(1:(N/2+1))/N);

%% Exercício 2-c

x = ((5000*5000)/1682);
X = abs(floor(x));

H1 = M1_abs;
H1(1:X) = 1;
H1(end) = 0;

H2 = M2_abs;
H2(1:X) = 1;
H2(end) = 0;

%% Exercício 2-d

V01p = 2*V1(1:N/2+1)/N;               %Somente frequências positivas
V02p = 2*V2(1:N/2+1)/N;

V01 = V01p.*H1;                       %Filtragem da frequência
V02 = V02p.*H2;

V01_abs = abs(2*V01(1:(N/2+1))/N);    %Módulo de V01(f)
V02_abs = abs(2*V02(1:(N/2+1))/N);

%% Exercício 2-e

V01esp = [V01(1:end-1) V01(end-1:-1:1)];     
V02esp = [V02(1:end-1) V02(end-1:-1:1)];

v01 = ifft(V01esp,'symmetric')*N; 
v02 = ifft(V02esp,'symmetric')*N;

%% Exercício 2-f

S = fft(s); 
S_abs = abs(2*S(1:(N/2+1))/N); 

figure(6)
subplot(4,1,1)
plot(f,S_abs)
grid on
title('Espectro de Frequência do Sinal Modulado S(f)')
xlabel('Frequência [kHz]')
ylabel('Amplitude [V]')
xlim([0 30])

figure(7)
subplot(4,1,1)
plot(f,S_abs)
grid on
title('Espectro de Frequência do Sinal Modulado S(f)')
xlabel('Frequência [kHz]')
ylabel('Amplitude [V]')
xlim([0 30])

figure(6)
subplot(4,1,2)
plot(f,V1_abs)
grid on
title('Espectro de Frequência do Sinal V1(f)')
xlabel('Frequência [kHz]')
ylabel('Amplitude [V]')
xlim([0 30])

figure(7)
subplot(4,1,2)
plot(f,V2_abs)
grid on
title('Espectro de Frequência do Sinal V2(f)')
xlabel('Frequência [kHz]')
ylabel('Amplitude [V]')
xlim([0 30])

figure(6)
subplot(4,1,3)
plot(f,H1)
grid on
title('Espectro Filtro Passa-Baixas H1(f)')
xlabel('Frequência [kHz]')
ylabel('Amplitude [V]')
xlim([0 30])

figure(7)
subplot(4,1,3)
plot(f,H2)
grid on
title('Espectro Filtro Passa-Baixas H2(f)')
xlabel('Frequência [kHz]')
ylabel('Amplitude [V]')
xlim([0 30])

figure(6)
subplot(4,1,4)
plot(f,V01_abs)
grid on
title('Espectro do Sinal de Áudio Recuperado V01(f)')
xlabel('Frequência [kHz]')
ylabel('Amplitude [V]')
xlim([0 30])

figure(7)
subplot(4,1,4)
plot(f,V02_abs)
grid on
title('Espectro do Sinal de Áudio Recuperado V02(f)')
xlabel('Frequência [kHz]')
ylabel('Amplitude [V]')
xlim([0 30])

%% Exercício 2-g

figure(8)
subplot(2,1,1)
plot(f,V01_abs)
grid on
title('Espectro V01(f)')
xlabel('Frequência [kHz]')
ylabel('Amplitude [V]')
xlim([0 2])

subplot(2,1,2)
plot(f,M1_abs)
grid on
title('Espectro M1(f)')
xlabel('Frequência [kHz]')
ylabel('Amplitude [V]')
xlim([0 2])

figure(9)
subplot(2,1,1)
plot(f,V02_abs)
grid on
title('Espectro V02(f)')
xlabel('Frequência [kHz]')
ylabel('Amplitude [V]')
xlim([0 2])

subplot(2,1,2)
plot(f,M2_abs)
grid on
title('Espectro M2(f)')
xlabel('Frequência [kHz]')
ylabel('Amplitude [V]')
xlim([0 2])

Audio1 = sprintf('Original')
sound(m1,fs)
pause(3.5);
 
Audio1 = sprintf('com Demodulador AM DSC-SC')
sound(v01,fs)
pause(3.5);

Audio2 = sprintf('Original')
sound(m2,fs)
pause(3.5);
 
Audio2 = sprintf('com Demodulador AM DSC-SC')
sound(v02,fs)
pause(3.5);


