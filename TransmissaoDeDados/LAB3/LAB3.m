%Lab 2
clear all
close all
clc
load audio

%Banda = 5kHz
fs = 176.4*10^3;
Ts = 1/fs;
%fc = frequÃªncia da portadora de alta frequÃªncia (Hz)
fc = 12*10^3;
% m(t) mensagem ou informação a ser enviada
mt1 = m1';
mt2 = m2';
N = length(mt1);


t = (0: N - 1)*Ts;

ct1 = cos(2*pi*fc.*t);
ct2 = sin(2*pi*fc.*t);

st1 = ct1.*mt1;
st2 = ct2.*mt2;

%% 1) (a)
figure(1)

subplot(3,1,1);
plot(t,mt1)
grid on
xlim([0.7 0.72])
title('m1(t)')
ylabel('amplitude')


subplot(3,1,2);
plot(t,ct1)
grid on
xlim([0.7 0.72])
title('c1(t)')
ylabel('amplitude')


subplot(3,1,3);
plot(t,st1)
grid on
xlim([0.7 0.72])
title('s1(t)')
ylabel('amplitude')


figure(2)
subplot(3,1,1);
plot(t,mt2)
grid on
xlim([0.7 0.72])
title('m2(t)')
ylabel('amplitude')


subplot(3,1,2);
plot(t,ct2)
grid on
xlim([0.7 0.72])
title('c2(t)')
ylabel('amplitude')


subplot(3,1,3);
plot(t,st2)
grid on
xlim([0.7 0.72])
title('s2(t)')
ylabel('amplitude')
grid off

%% 1) (b)

M = fft(mt1);

M2 = (M(1:((N/2) + 1))*2)/N;
f = linspace(0,fs/2000,(N/2 + 1));
figure(3)
subplot(3,1,1);
plot(f,abs(M2))
grid on
xlim([0 18])
title('Aplicando fft em mt1')
ylabel('amplitude')

subplot(3,1,2);

G = fft(ct1);
G2 = (G(1:(N/2 + 1))*2)/N;
f = linspace(0,fs/2000,(N/2 + 1));
plot(f,abs(G2))
title('Aplicando fft em ct1')
xlim([0 18])
xlabel('f(kHz)')
ylabel('fft(c1(t))')

% subplot(3,1,2);
% plot(t,ct1)
% grid on
% xlim([0 18])
% title('c1(t)')
% ylabel('amplitude')
% 
% 
% subplot(3,1,3);
% plot(t,st1)
% grid on
% xlim([0 18])
% title('s1(t)')
% ylabel('amplitude')
% 
% 
% figure(2)
% subplot(3,1,1);
% plot(t,mt2)
% grid on
% xlim([0 18])
% title('m2(t)')
% ylabel('amplitude')
% 
% 
% subplot(3,1,2);
% plot(t,ct2)
% grid on
% xlim([0.7 0.72])
% title('c2(t)')
% ylabel('amplitude')
% 
% 
% subplot(3,1,3);
% plot(t,st2)
% grid on
% xlim([0.7 0.72])
% title('s2(t)')
% ylabel('amplitude')
% grid off

% subplot(3,1,1);
% plot(t,mt)
% title('m(t)')
% xlabel('tempo(s)')
% ylabel('amplitude')
% grid on
% subplot(3,1,2);
% plot(t,ct)
% title('c(t)')
% xlabel('tempo(s)')
% ylabel('amplitude')
% grid on
% subplot(3,1,3);
% plot(t,st)
% title('s(t)')
% xlabel('tempo(s)')
% ylabel('amplitude')
% grid on
% 
% 
% figure(2)
% 
% 
% subplot(3,1,1);
% plot(t,mt)
% title('m(t)')
% xlim([0.4 0.42])
% xlabel('tempo(s)')
% ylabel('amplitude')
% grid on
% subplot(3,1,2);
% plot(t,ct)
% title('c(t)')
% xlim([0.4 0.42])
% xlabel('tempo(s)')
% ylabel('amplitude')
% grid on
% subplot(3,1,3);
% plot(t,st)
% title('s(t) e m(t)')
% xlim([0.4 0.42])
% xlabel('tempo(s)')
% ylabel('amplitude')
% grid on
% hold on 
% plot(t,mt,'k')
% hold off
% 
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% c)
% 
% figure(3)
% 
% subplot(3,1,1);
% 
% G = fft(mt);
% 
% G2 = (G(1:(N/2 +1))*2)/N;
% f = linspace(0,fs/2000,(N/2 +1));
% 
% 
% plot(f,abs(G2))
% title('Aplicando fft em mt')
% xlim([0 18])
% xlabel('f(kHz)')
% ylabel('fft(m(t))')
% 
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%
% subplot(3,1,2);
% 
% G = fft(ct);
% 
% G2 = (G(1:(N/2 +1))*2)/N;
% f = linspace(0,fs/2000,(N/2 +1));
% 
% 
% plot(f,abs(G2))
% title('Aplicando fft em ct')
% xlim([0 18])
% xlabel('f(kHz)')
% ylabel('fft(c(t))')
% 
% %%%%%%%%%%%%%%%%%%%%%%%%%%%
% 
% subplot(3,1,3);
% 
% G = fft(st);
% 
% G2 = (G(1:(N/2 +1))*2)/N;
% f = linspace(0,fs/2000,(N/2 +1));
% 
% plot(f,abs(G2))
% title('Aplicando fft em st')
% xlim([0 18])
% xlabel('f(kHz)')
% ylabel('fft(s(t))')
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% d)
% 
% figure(4)
% subplot(3,1,1);
% 
% fs = 1/Ts;
% 
% pwelch(mt,[],[],1024,fs);
% 
% 
% subplot(3,1,2);
% 
% pwelch(ct,[],[],1024,fs);
% 
% subplot(3,1,3);
% 
% pwelch(st,[],[],1024,fs);
% 
% % 2)
% 
% a)
% 
% figure(5)
% 
% subplot(3,1,1);
% 
% vt = st.*cos(2*pi*fc.*t);
% 
% plot(t,vt)
% xlabel('tempo(s)')
% ylabel('Tensão(V)')
% title('demodulação síncrona')
% % exercício b
% figure(6)
% H = (f < 5  );
% plot(f,H)
% xlabel('f(Hz)')
% ylabel('H(f)')
% title('Filtro passa-baixas')
% 
% % Obtendo a fft de v(t), exercício (c)
% 
% V = fft(vt);
% 
% V1 = (V(1:(N/2 + 1))*2)/N;
% 
% V0 = V1.*H;
% figure(7)
% plot(f,abs(V0))
% title('Filtragem na frequência')
% xlabel('f(Hz)')
% ylabel('V0(f)')
% 
% % exercício (d)
% 
% V0espelhado = [V0(1:end-1) V0(end-1:-1:1)];  
% 
% v0 = ifft(V0espelhado,'symmetric')*N;
% 
% V0 = fft(v0);
% 
% V2 = (V0(1:(N/2 + 1))*2)/N;
% 
% 
% figure(8)
% 
% subplot(4,1,1);
% plot(f,abs(G2))% (i) o espectro de frequ^encias do sinal modulado S(f).
% xlim([0 30])
% ylabel('S(f)')
% title('Sinal Recuperado')
% 
% (ii) o espectro de frequ^encias do sinal V (f),
% subplot(4,1,2);
% plot(f,abs(V1))
% xlim([0 30])
% ylabel('V(f)')
% (iii) o espectro filtro passa-baixas H(f).
% subplot(4,1,3)
% plot(f,H)
% xlim([0 30])
% ylabel('H(f)')
% (iii) o espectro do sinal de audio recuperado apos a filtragem na frequência V 0(f).
% 
% subplot(4,1,4)
% plot(f,abs(V2))
% 
% xlim([0 30])
% ylabel('V0(f)')
% xlabel('f(kHz)')
% 
% sound(m, fs)% mensagem original
% 
% sound(v0,fs)% mensagem demodulada
% 
% % 3)
% 
% 
%  vt = st.*cos(2*pi*fc.*t + pi/3);Cai a amplitude do sinal
%  
%  
%  vt = st.*cos(2*pi*fc.*t + pi/2); sinal não aparece o som porque o sinal some,
%  devido à fase de modulação
