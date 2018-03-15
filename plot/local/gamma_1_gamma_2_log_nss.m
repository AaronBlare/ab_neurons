data_path = '../../data/plane';

fin = 4;
b = 4.0;

suffix = sprintf('log_nss_system(1)_gamma1(0.0000)_gamma2(5.0000)_fin(%0.4f)_b(%0.4f)_etaw(8.0000)', ...
    fin, ...
    b);

fn = sprintf('%s/gamma_1_from_gamma_2_%s.txt', ...
    data_path, ...
    suffix);

data = importdata(fn);

g1 = data(:, 1);
g2 = data(:, 2);
etas = data(:, 3);

eta_data = zeros(51);
eta_count = 1;

for g1_id = 1:51
    for g2_id = 1:51
        eta_data(g1_id, 51-g2_id+1) = etas(eta_count);
        eta_count = eta_count+1;
    end
end

gamma1 = (-5:0.1:0);
gamma2 = (5:-0.1:0);
imagesc(gamma1,gamma2,eta_data');
set(gca,'Ydir','Normal');
set(gca, 'FontSize', 30);
xlabel('$\gamma_G$', 'Interpreter', 'latex');
set(gca, 'FontSize', 30);
ylabel('$\gamma_D$', 'Interpreter', 'latex');
colormap hot;
h = colorbar;
set(gca, 'FontSize', 30);
title(h, '$log_{10}(NSS)$', 'FontSize', 33, 'Interpreter', 'latex');
set(gca,'YDir','normal');
hold all;