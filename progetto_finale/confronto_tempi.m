nodi = [25, 50, 75, 100, 125, 150, 175, 200];


tempi_depina = [1991, 12079, 53297, 358045, 163675, 247408, 229378, 662193]; 
tempi_dfs    = [2500, 18700, 66113, 201786, 203830, 313744, 365322, 740526];


figure('Name', 'Confronto temporale tra De-Pina e DFS', 'NumberTitle', 'off');

plot(nodi, tempi_depina, '-o', 'LineWidth', 2, 'MarkerSize', 6, 'Color', [0 0.4470 0.7410]); 
hold on;
plot(nodi, tempi_dfs, '-^', 'LineWidth', 2, 'MarkerSize', 6, 'Color', [0.8500 0.3250 0.0980]);   

title('Confronto delle Prestazioni per la Ricerca dei Cicli Fondamentali', 'FontSize', 14, 'FontWeight', 'bold');
xlabel('Dimensione del Grafo (Numero di Nodi)', 'FontSize', 12);
ylabel('Tempo di Esecuzione (\mus - Microsecondi)', 'FontSize', 12);


grid on;
set(gca, 'GridLineStyle', ':', 'GridAlpha', 0.6, 'FontSize', 11);
set(gca, 'XTick', nodi); 


legend('Algoritmo di De Pina', 'Algoritmo DFS', 'Location', 'NorthWest', 'FontSize', 11);

saveas(gcf, 'grafico_prestazioni_pcs.png');