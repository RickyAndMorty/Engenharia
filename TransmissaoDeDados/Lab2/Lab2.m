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
% m(t) mensagem ou informa��o a ser enviada
mt = m';
N = length(mt);

t = (0: N - 1)*Ts;

ct = cos(2*pi*fc.*t);

st = ct.*mt;

figure(1)

subplot(3,1,1);
plot(t,mt)
title('m(t)')
%xlabel('tempo(s)')
ylabel('amplitude')
grid on
subplot(3,1,2);
plot(t,ct)
title('c(t)')
%xlabel('tempo(s)')
ylabel('amplitude')
grid on
subplot(3,1,3);
plot(t,st)
title('s(t)')
xlabel('tempo(s)')
ylabel('amplitude')
grid on


figure(2)


subplot(3,1,1);
plot(t,mt)
title('m(t)')
xlim([0.4 0.42])
%xlabel('tempo(s)')
ylabel('amplitude')
grid on
subplot(3,1,2);
plot(t,ct)
title('c(t)')
xlim([0.4 0.42])
%xlabel('tempo(s)')
ylabel('amplitude')
grid on
subplot(3,1,3);
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

subplot(3,1,1);

G = fft(mt);

G2 = (G(1:(N/2 +1))*2)/N;
f = linspace(0,fs/2000,(N/2 +1));


plot(f,abs(G2))
title('Aplicando fft em mt')
xlim([0 18])
xlabel('f(kHz)')
ylabel('fft(m(t))')

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
subplot(3,1,2);

G = fft(ct);

G2 = (G(1:(N/2 +1))*2)/N;
f = linspace(0,fs/2000,(N/2 +1));


plot(f,abs(G2))
title('Aplicando fft em ct')
xlim([0 18])
xlabel('f(kHz)')
ylabel('fft(c(t))')

%%%%%%%%%%%%%%%%%%%%%%%%%%%%

subplot(3,1,3);

G = fft(st);

G2 = (G(1:(N/2 +1))*2)/N;
f = linspace(0,fs/2000,(N/2 +1));

plot(f,abs(G2))
title('Aplicando fft em st')
xlim([0 18])
xlabel('f(kHz)')
ylabel('fft(s(t))')
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%d)

figure(4)
subplot(3,1,1);

fs = 1/Ts;

pwelch(mt,[],[],1024,fs);


subplot(3,1,2);

pwelch(ct,[],[],1024,fs);

subplot(3,1,3);

pwelch(st,[],[],1024,fs);

%% 2)

%a)

figure(5)

subplot(3,1,1);

vt = st.*cos(2*pi*fc.*t);

plot(t,vt)
%% exerc�cio b
figure(6)
H = (f < 5  );
plot(f,H)

%% Obtendo a fft de v(t), exerc�cio (c)

V = fft(vt);

V1 = (V(1:(N/2 + 1))*2)/N;

V0 = V1.*H;
figure(7)
plot(f,abs(V0))

%V0 = H.*V;















