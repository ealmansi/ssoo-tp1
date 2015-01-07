eficiencia_1_c = csvread('eficiencia_1_c.csv');
eficiencia_2_c = csvread('eficiencia_2_c.csv');
eficiencia_3_c = csvread('eficiencia_3_c.csv');
eficiencia_4_c = csvread('eficiencia_4_c.csv');

close all;
figure; hold on;
plot(eficiencia_1_c(1:70,1), eficiencia_1_c(1:70,2), 'r');
plot(eficiencia_2_c(1:70,1), eficiencia_2_c(1:70,2), 'g');
plot(eficiencia_3_c(1:70,1), eficiencia_3_c(1:70,2), 'b');
plot(eficiencia_4_c(1:70,1), eficiencia_4_c(1:70,2), 'black');
title('Eficiencia vs Quantum: 1, 2, 3 y 4 nucleos');xlabel('Quantum');ylabel('Eficiencia (cant. ticks utiles/cant. ticks total)');
legend({'1 nucleo', '2 nucleos', '3 nucleos', '4 nucleos'});
set(gcf(), 'PaperPositionMode', 'auto');
saveas(gcf(), 'eficiencia_compracion.png', 'png');