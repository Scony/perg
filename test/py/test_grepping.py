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
