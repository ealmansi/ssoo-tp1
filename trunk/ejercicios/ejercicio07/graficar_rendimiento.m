rendimiento_1_c = csvread('rendimiento_1_c.csv');
rendimiento_2_c = csvread('rendimiento_2_c.csv');
rendimiento_3_c = csvread('rendimiento_3_c.csv');
rendimiento_4_c = csvread('rendimiento_4_c.csv');

close all;
figure; hold on;
plot(rendimiento_1_c(1:70,1), 6./rendimiento_1_c(1:70,2), 'r');
plot(rendimiento_2_c(1:70,1), 6./rendimiento_2_c(1:70,2), 'g');
plot(rendimiento_3_c(1:70,1), 6./rendimiento_3_c(1:70,2), 'b');
plot(rendimiento_4_c(1:70,1), 6./rendimiento_4_c(1:70,2), 'black');
title('Rendimiento vs Quantum: 1, 2, 3 y 4 nucleos');xlabel('Quantum');ylabel('Rendimiento (cant. tareas completadas por tick)');
legend({'1 nucleo', '2 nucleos', '3 nucleos', '4 nucleos'});
set(gcf(), 'PaperPositionMode', 'auto');
saveas(gcf(), 'rendimiento_comparacion.png', 'png');