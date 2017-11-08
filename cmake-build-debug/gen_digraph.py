
lines = open('net_diagram/results.txt', 'r').readlines()
lines_out = open('net_diagram/results.digraph', 'w')

lines_out.write('digraph G {')
for i in range(0, len(lines)):
    ends = lines[i].split(',')
    for end in ends:
        lines_out.write(str(i) + ' -> ' + '%s;' % end)
lines_out.write('}')
