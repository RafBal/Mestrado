clc
%clear all
close all;
k = 1;
q = 3; % número de baterias
str_file = 'Conf_157.xlsx';
planilha = 'Bateria1';
matrix_pmax = zeros(9,q);
vector_pmax = zeros(1,9*q);
matrix_freqmax = zeros(9,q);
vector_freqmax = zeros(1,9*q);
curvas = zeros(288,9,q);


desv_freq = zeros(9,1);
desv_pmax = zeros(9,1);
mean_freq = desv_freq;
mean_pmax = desv_freq;
median_freq = mean_freq;
median_pmax = mean_freq;

curveb = cell(1,9);

freq = xlsread('Conf_13.xlsx','Bateria3','K:K');

while k <= q
    % Extraindo as curvas:
curveb_H2O = xlsread(str_file,planilha,'A1:A288');
curveb_H2O(146,1) = (curveb_H2O(145,1)+curveb_H2O(147,1))/2;
curveb_10 = xlsread(str_file,planilha,'B1:B288');
curveb_10(146,1) = (curveb_10(145,1)+curveb_10(147,1))/2;
curveb_25 = xlsread(str_file,planilha,'C1:C288');
curveb_25(146,1) = (curveb_25(145,1)+curveb_25(147,1))/2;
curveb_50 = xlsread(str_file,planilha,'D1:D288');
curveb_50(146,1) = (curveb_50(145,1)+curveb_50(147,1))/2;
curveb_75 = xlsread(str_file,planilha,'E1:E288');
curveb_75(146,1) = (curveb_75(145,1)+curveb_75(147,1))/2;
curveb_90 = xlsread(str_file,planilha,'F1:F288');
curveb_90(146,1) = (curveb_90(145,1)+curveb_90(147,1))/2;
curveb_94 = xlsread(str_file,planilha,'G1:G288');
curveb_94(146,1) = (curveb_94(145,1)+curveb_94(147,1))/2;
curveb_97 = xlsread(str_file,planilha,'H1:H288');
curveb_97(146,1) = (curveb_97(145,1)+curveb_97(147,1))/2;
curveb_100 = xlsread(str_file,planilha,'I1:I288');
curveb_100(146,1) = (curveb_100(145,1)+curveb_100(147,1))/2;

curveb = {curveb_H2O, curveb_10, curveb_25, curveb_50, curveb_75, curveb_90, curveb_94, curveb_97, curveb_100}; 
for j = 1:9

    curve_now = curveb{1,j};
curvas(:,j,k) = curve_now;
    % Extraindo pico máximo:
    matrix_pmax(j,k) = max(curve_now);
    % Extraindo frequências dos picos máximos:
    for i = 1:288
        if matrix_pmax(j,k) == curve_now(i,1)
            i_max = i;
        end
    end
    matrix_freqmax(j,k) = freq(i_max,1);
%     for i = 1:288
%     curve_now(i,1) = curve_now(i,1)-min(curve_now)./(max(curve_now)-min(curve_now));
     
%     end
end
    planilha = 'Bateria';
k = k + 1;
l = num2str(k);
planilha = strcat(planilha,l); 

end
freqmax = zeros(1,q);
pmax = zeros(1,q);
m = 0;

desv_pmax2 = desv_pmax;
matrix_pp = matrix_pmax;

for j = 1:9
desv_pmax2(j,1) = std(matrix_pp(j,:))./max(matrix_pp(j,:));
end

for k = 1:q
matrix_pmax(:,k) = (matrix_pmax(:,k)-min(matrix_pmax(:,k)))./(max(matrix_pmax(:,k))-min(matrix_pmax(:,k)));
end



for j = 1:9
    desv_freq(j,1) = std(matrix_freqmax(j,:));
    desv_pmax(j,1) = std(matrix_pmax(j,:));
    mean_freq(j,1) = mean(matrix_freqmax(j,:));
    mean_pmax(j,1) = mean(matrix_pmax(j,:));
    median_freq(j,1) = median(matrix_freqmax(j,:));
    median_pmax(j,1) = median(matrix_pmax(j,:));
 
    pmax = matrix_pmax(j,:);
    freqmax = matrix_freqmax(j,:);
    for w = 1:q
        vector_pmax(1,w + m) = pmax(1,w);
        vector_freqmax(1,w + m) = freqmax(1,w);
    end
    m = m + q;
end

 matrix_freqmax = matrix_freqmax/881.9583901;
 curveb_percent = [0,10,25,50,75,90,94,97,100];
 
 
 lambda_freq = zeros(9,1);
for i = 2:9
    
lambda_freq(i,1) = abs(mean_freq(i,1)-mean_freq(i-1,1)) + lambda_freq(i-1,1);

end
 
 

%matrix_pmax = matrix_pmax.*1023;
 matrix_freqmax = matrix_freqmax.*881.9583901;
  mean_matrix_freqmax = zeros(9,1);
mean_matrix_pmax = zeros(9,1);
for j = 1:9
mean_matrix_pmax(j,1) = mean(matrix_pmax(j,:));
mean_matrix_freqmax(j,1) = mean(matrix_freqmax(j,:));

end
desv_freq = desv_freq/max(mean_matrix_freqmax);

for j = 1:9
        desv_pmax(j,1) = std(matrix_pmax(j,:))/max(matrix_pmax(j,:));%/mean_matrix_pmax(j,:);
end

%mean_matrix_freqmax = mean_matrix_freqmax/max(mean_matrix_freqmax);


mean_matrix_pmax = (mean_matrix_pmax- min(mean_matrix_pmax))/(max(mean_matrix_pmax)-min(mean_matrix_pmax));

%__________________________


%subplot(3,1,1)
meancurvas = zeros(288,9);% mean(curvas,3);
valor_max = max(max(max(curvas)));

     for i = 1:9
        for j = 1:288
            meancurvas(j,i) = mean(curvas(j,i,:));
                     meancurvas(j,i) = meancurvas(j,i)./valor_max;
                    
        end
     end
% figure
% 
% plot(curveb_percent,matrix_pmax(:,1))
% hold on 
% plot(curveb_percent,matrix_pmax(:,2))
% hold on 
% plot(curveb_percent,matrix_pmax(:,3))
% hold on 
% plot(curveb_percent,matrix_pmax(:,4))
% hold on 
% plot(curveb_percent,matrix_pmax(:,5))
% legend("1","2","3","4","5")
plot(freq,meancurvas)
% legend('mean curve', 'round 1', 'round 2', 'round 3')
title('Configuration number 157 - mean of the curves')
legend('0%','10%','25%','50%','75%','90%','94%','97%','100%')

%subplot(3,1,2)
figure
errorbar(curveb_percent,mean_matrix_pmax,desv_pmax2)
title('Configuration number 157 - normalized amplitude evolution')
ylabel('Normalized amplitude')
xlabel('% of MEG')
%figure

%subplot(3,1,3)
figure
xx = 0:1:100;
yy = spline(curveb_percent,lambda_freq,xx);
p = polyfit(xx,yy,3);
f = polyval(p,curveb_percent);
    f(1,1) = 0;
     f1 = zeros(9,1);
f = f';
for i = 2:9
    
f1(i,1) = abs(f(i,1)-f(i-1,1)) + f1(i-1,1);

end
plot(curveb_percent,lambda_freq,'ok');%,curveb_percent,f);
title('Configuration number 157 - wavelength shift evolution')
ylabel('Wavelength shift [nm]')
xlabel('% of MEG')
