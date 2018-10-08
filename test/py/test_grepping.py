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


def test_greps_switching_in_circle(executable_path, tmpdir):
    lines = ['foo {}'.format(i) for i in range(5)] + ['bar {}'.format(i) for i in range(5)]
    greps = [
        lines,
        [line for line in lines if 'bar' in line],
        [line for line in lines if 'bar' in line and '0' in line],
    ]

    def check_term_lines(term, lines_included, lines_not_included):
        term.await_text(lines_included[0])
        screenshot = term.screenshot()
        for line in lines_included:
            assert line in screenshot
        for line in lines_not_included:
            assert line not in screenshot

    text_file_path = tmpdir.join('regular_file.txt')
    with text_file_path.open('w') as fh:
        fh.write('\n'.join(lines))

    with Runner(executable_path, str(text_file_path)) as term:
        for line in lines:
            term.await_text(line)
        for c in 'gbar':
            term.press(c)
        term.press('Enter')
        for c in 'gbar 0':
            term.press(c)
        term.press('Enter')

        check_term_lines(term, greps[2], set(lines) - set(greps[2]))
        term.press('S-Left')
        check_term_lines(term, greps[1], set(lines) - set(greps[1]))
        term.press('S-Left')
        check_term_lines(term, greps[0], set(lines) - set(greps[0]))
        term.press('S-Left')
        check_term_lines(term, greps[2], set(lines) - set(greps[2]))
        term.press('S-Right')
        check_term_lines(term, greps[0], set(lines) - set(greps[0]))

        term.press('q')
