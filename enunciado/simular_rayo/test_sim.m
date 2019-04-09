%% Levanto la imagen y la muestro
arch = 'tomo3.png';
I = imread(arch);

% si es RGB la paso a escala de grises
if size(I,3) > 2
 I = I(:,:,1)/3 + I(:,:,2)/3 + I(:,:,3)/3;
end

figure;
% otra forma de mostrar es con imshow(I); 
imagesc(I); colormap(gray); axis image;

[f,c] = size(I);

%%
f_ini = 50; c_ini = 1;  % coordenada inicial
f_fin = 350; c_fin = c; % coordenada final
dibujar = 1;
n = 100; m = 100; % tamano de la discretizacion
[t,R] = simularRayo(I, n, m, f_ini, c_ini, f_fin, c_fin, dibujar);

%%
figure, imagesc(R), colorbar;
title('Matriz de discretizaciones con los dij para el rayo simulado')


