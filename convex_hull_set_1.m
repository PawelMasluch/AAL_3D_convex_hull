clear;
clc;


% Tablica punktow 3D;
    % wiersze - kolejne punkty
    % kolumny - wspolrzedne x,y,z
Points =    [
                0 0 0;
                10 0 0;
                0 10 0;
                0 0 10;
                2 2 2;
                1 1 1;
                0.5 0.5 0.5;
                7 7 7;
                %-20 -20 -20
            ];


% Wyodrebnienie konkretnych 
% wspolrzednych punktow
x = Points(:, 1);
y = Points(:, 2);
z = Points(:, 3);


% Wynaczenie otoczki wypuklej
[faces] = convhull(x, y, z);


% Wykres 1. 
% Chmura punktow oraz znaleziona otoczka wypukla (szkielet)
figure(1);
hold on;

    % chmura punktow
    plot3(x, y, z, '*');
    
    % otoczka wypukla
    trisurf(faces, x, y, z, 'FaceColor', 'none'); 
    
    % opcje wykresu
    axis equal;
    title('3D convex hull (skeleton)');
    xlabel('x');
    ylabel('y');
    zlabel('z');

hold off;



% Wykres 2. 
% Znaleziona otoczka wypukla (kolorowe sciany trojkatne)
figure(2);
hold on;

    % otoczka wypukla
    trisurf(faces, x, y, z, 'FaceColor', 'green');
    
    % opcje wykresu
    axis equal;
    title('3D convex hull (colored faces)');
    xlabel('x');
    ylabel('y');
    zlabel('z');

hold off;
