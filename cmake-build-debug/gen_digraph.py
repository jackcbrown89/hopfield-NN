mems = [38, 25]
lines = open('net_diagram/results.txt', 'r').readlines()
lines_out = open('net_diagram/results1.digraph', 'w')

lines_out.write('digraph G {')
[lines_out.writelines('%s [shape=circle, style=filled, fillcolor=red]' % x) for x in mems]
for i in range(0, len(lines)):
    if i not in mems:
        ends = lines[i].split(',')
        for end in ends:
            lines_out.write(str(i) + ' -> ' + '%s;' % end)
lines_out.write('}')
