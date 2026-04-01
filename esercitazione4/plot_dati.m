% uso matlab per plottare i dati ottenuti tramite il programma cpp 
%%
%%%
% i dati in N rappresentano le dimensioni dei vettori da sortare
% sicuramente esiste un metodo più intelligente io ho deciso di stampare a
% terminale i valori ottenuti per ogni algoritmo in un vettore di
% dimensioni 12, per poi copiare e incollare i valori su matlab(
N=[4,8,16,32,64,128,256,512,1024,2048,4096,8192];

bubble=[4e-07,7e-07,2.2e-06,8.701e-06,3.0004e-05,0.000103612,0.000410749,0.00186342,0.00817807,0.037176,0.123234,0.616293];
insertion=[3e-07,4e-07,1.1e-06,3.401e-06,1.0401e-05,3.1104e-05,0.00017582,0.000553966,0.00214045,0.00766581,0.0330679,0.137177];
selection=[3e-07,7e-07,1.701e-06,5.2e-06,1.6602e-05,5.8207e-05,0.000217625,0.00209275,0.00331809,0.0120555,0.0499318,0.197385];
t_sort=[9e-07,8e-07,1.8e-06,5.801e-06,1.1502e-05,5.0006e-05,5.8207e-05,0.000157718,0.000272432,0.00051216,0.00110373,0.00280883];
%% prima lo faccio con plot
figure('Name', 'Analisi Lineare');
plot(N, bubble, '-ro', 'DisplayName', 'Bubble Sort');
hold on;
plot(N, insertion, '-bs','DisplayName', 'Insertion Sort');
plot(N, selection, '-gd', 'DisplayName', 'Selection Sort');
plot(N, t_sort, '-k*','DisplayName', 'std::sort');
xlabel('Dimensione Array N');
ylabel('Tempo di Esecuzione (s)');
hold off;
%% poi in scala logaritmica
figure('Name', 'Analisi Log-Log');
loglog(N, bubble, '-ro','DisplayName', 'Bubble Sort');
hold on;
loglog(N, insertion, '-bs','DisplayName', 'Insertion Sort');
loglog(N, selection, '-gd','DisplayName', 'Selection Sort');
loglog(N, t_sort, '-k*','DisplayName', 'std::sort');
xlabel('Dimensione Array N');
ylabel('Tempo di Esecuzione (s)');
hold off;