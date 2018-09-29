from hecate.hecate import Runner


def test_inital_grepping(executable_path, tmpdir):
    lines = ['line {}'.format(i) for i in range(5)]
    text_file_path = tmpdir.join('regular_file.txt')
    with text_file_path.open('w') as fh:
        fh.write('\n'.join(lines))
    with Runner(executable_path, str(text_file_path)) as term:
        for line in lines:
            term.await_text(line)
        term.press('g')
        term.press('0')
        term.press('Enter')
        term.await_text(lines[0])
        assert lines[1] not in term.screenshot()
        term.press('q')


def test_2_greps(executable_path, tmpdir):
    lines = ['line {}'.format(i) for i in range(5)]
    rows = ['row {}'.format(i) for i in range(5)]
    text_file_path = tmpdir.join('regular_file.txt')
    with text_file_path.open('w') as fh:
        fh.write('\n'.join(lines + rows))
    with Runner(executable_path, str(text_file_path)) as term:
        for line in lines:
            term.await_text(line)
        for row in rows:
            term.await_text(row)
        term.press('g')
        for c in 'row':
            term.press(c)
        term.press('Enter')
        term.await_text(rows[0])
        assert 'line' not in term.screenshot()
        term.press('g')
        term.press('0')
        term.press('Enter')
        term.await_text(rows[0])
        assert 'line' not in term.screenshot()
        assert rows[1] not in term.screenshot()
        term.press('q')
