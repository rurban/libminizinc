% RUNS ON mzn20_fd
% RUNS ON mzn-fzn_fd
% RUNS ON mzn20_fd_linear
% RUNS ON mzn20_mip
%% Check that the smallest first search complies with spec
%%

var 1..10: x;
var 2..10: y;
constraint x = 1 -> y > 10;
constraint x > 1 -> x > 4;
constraint x + y <= 11;

solve :: int_search([x,y],smallest,indomain_min,complete)
                maximize x + y;

output ["%% test-small1.mzn: output should be x = 9, y = 2\nx = ",
         show(x),";\ny = ",show(y),";\n"];
