function [t, D] = simularRayo(I, n, m, f_ini, c_ini, f_fin, c_fin, dibujar)
%SIMULARRAYO Simula la emision de un rayo tomografico sobre una imagen.
    % [t, R] = simularRayo(I, n, m, f_ini, c_ini, f_fin, c_fin, [dibujar])
    %
    % Simula un rayo del tomagrafo a traves de la imagen I, discretizada en
    % n filas y m columnas. El rayo tiene como punto inicial el punto
    % (f_ini, c_ini) y como punto final el punto (f_ini, c_ini).
    % Retorna: el tiempo total t de la emision del rayo y las distancias
    % recorridas R(i,j) en cada punto de la discretizacion.
    % El parametro dibujar es opcional y si vale 1 se dibuja el rayo sobre
    % la imagen.
    
    [f, c] = size(I);
    df = f/n;
    dc = c/m;
    
    t = 0;
    D = zeros(n,m);
    
    % Lo siguiente es una chanchada para poder simplificarme la vida usando
    % polyfit mas adelante
    if f_ini == f_fin
        f_ini = f_ini - 0.5;
        f_fin = f_fin + 0.5;
    end
    if c_ini == c_fin
        c_ini = c_ini - 0.5;
        c_fin = c_fin + 0.5;
    end    
    
    % Calculo la recta que representa el rayo (y su inversa)
    % Tambien se puede calcular sin polyfit usando la ecuaci�n de una recta
    Pi = polyfit([f_ini, f_fin], [c_ini, c_fin], 1);
    Pj = polyfit([c_ini, c_fin], [f_ini, f_fin], 1);
    
    % Lo dibujo si pidieron
    if nargin < 8 || dibujar == 1
        figure;
        imagesc(I), colormap(gray), axis image;
        hold on;
        %Dibuja una l�nea desde (f_ini, c_ini) hasta (f_fin, c_fin) 
        plot([c_ini, c_fin], [f_ini, f_fin], 'Color', 'r', 'LineStyle', '-', 'LineWidth',1.5);
        title('Rayo sobre la img original de datos tomograficos')
    end
    
    % obtengo las filas entre las que esta el rayo para no tener que recorrerlas todas
    i1 = polyval(Pj, 1);
    i2 = polyval(Pj, c);
    i_min = max(1, min(f-1, ceil(min(i1,i2))));
    i_max = max(1, min(f-1, ceil(max(i1,i2))));

    % recorro cada fila (entre i_min e i_max) y veo que columnas toca el rayo
    for i = i_min : i_max
        j1 = polyval(Pi, i-1);
        j2 = polyval(Pi, i);
        j_min = max(1, min(c, ceil(min(j1,j2))));
        j_max = max(1, min(c, ceil(max(j1,j2))));
        for j = j_min : j_max
            % tomo los datos del pixel (i,j)
            t = t + tiempoEn(double(I(i,j)));            
            n_i = min(n, fix(i/df) + 1);
            m_j = min(m, fix(j/dc) + 1);
            D(n_i, m_j) = D(n_i, m_j) + 1;   
        end
    end
 end

function t = tiempoEn(densidad)
    % Indica cuanto tarda la se�al en recorrer un pixel de cierta densidad
    t = (densidad+1);
end
