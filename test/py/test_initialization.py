import pytest
from hecate.hecate import Runner


def test_initial_screen(executable_path):
    with Runner(executable_path) as term:
        term.await_text('Welcome to perg')
        term.press('q')


def test_initial_screen_with_file(executable_path, tmpdir):
    lines = ['line {}'.format(i) for i in range(5)]
    text_file_path = tmpdir.join('regular_file.txt')
    with open(text_file_path, 'w') as fh:
        fh.write('\n'.join(lines))
    with Runner(executable_path, str(text_file_path)) as term:
        for line in lines:
            term.await_text(line)
        term.press('q')


def test_initial_screen_with_nonexistent_file(executable_path):
    with Runner(executable_path, 'path_to_file') as term:
        term.await_text('Welcome to perg')
        term.press('q')


def test_initial_status_bar(executable_path):
    with Runner(executable_path) as term:
        term.await_text('-- dummy status --')
        term.press('q')


@pytest.mark.parametrize('help_opt', ['-h', '--help'])
def test_help_screen(executable_path, help_opt):
    with Runner(executable_path, help_opt) as term:
        term.await_text('Usage:')
