%Lab 2
clear all
close all
clc
load audio
%Banda = 5kHz
fs = 176.4*10^3;
Ts = 1/fs;
%fc = frequência da portadora de alta frequência (Hz)
fc = 12*10^3;
% m(t) mensagem ou informação a ser enviada
mt = m';
N = length(mt);

t = (0: N - 1)*Ts;

ct = cos(2*pi*fc.*t);

st = ct.*mt;

figure(1)

aux=subplot(3,1,1);
plot(t,mt)
title('m(t)')
%xlabel('tempo(s)')
ylabel('amplitude')
grid on
aux=subplot(3,1,2);
plot(t,ct)
title('c(t)')
%xlabel('tempo(s)')
ylabel('amplitude')
grid on
aux=subplot(3,1,3);
plot(t,st)
title('s(t)')
xlabel('tempo(s)')
ylabel('amplitude')
grid on


figure(2)


aux=subplot(3,1,1);
plot(t,mt)
title('m(t)')
xlim([0.4 0.42])
%xlabel('tempo(s)')
ylabel('amplitude')
grid on
aux=subplot(3,1,2);
plot(t,ct)
title('c(t)')
xlim([0.4 0.42])
%xlabel('tempo(s)')
ylabel('amplitude')
grid on
aux=subplot(3,1,3);
plot(t,st)
title('s(t) e m(t)')
xlim([0.4 0.42])
xlabel('tempo(s)')
ylabel('amplitude')
grid on
hold on 
plot(t,mt,'k')
hold off

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%c)

figure(3)

aux=subplot(3,1,1);

G = fft(mt);

G2 = (G(1:(N/2 +1))*2)/N;
f = linspace(0,fs/2000,(N/2 +1));


plot(f,abs(G2))
title('Aplicando fft em mt')
xlim([0 18])
xlabel('f(kHz)')
ylabel('fft(m(t))')

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
aux=subplot(3,1,2);

G = fft(ct);

G2 = (G(1:(N/2 +1))*2)/N;
f = linspace(0,fs/2000,(N/2 +1));


plot(f,abs(G2))
title('Aplicando fft em ct')
xlim([0 18])
xlabel('f(kHz)')
ylabel('fft(c(t))')

%%%%%%%%%%%%%%%%%%%%%%%%%%%%

aux=subplot(3,1,3);

G = fft(st);

G2 = (G(1:(N/2 +1))*2)/N;
f = linspace(0,fs/2000,(N/2 +1));


plot(f,abs(G2))
title('Aplicando fft em st')
xlim([0 18])
xlabel('f(kHz)')
ylabel('fft(s(t))')



