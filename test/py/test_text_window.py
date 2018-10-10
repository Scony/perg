import sys

import pytest
from hecate.hecate import Runner


ROWS = 32
TEXT_ROWS = ROWS - 2
COLS = 128


@pytest.fixture(scope='function')
def temporary_text_file(lines, tmpdir):
    text_file_path = tmpdir.join('regular_file.txt')
    with text_file_path.open('w') as fh:
        fh.write('\n'.join(lines))
    return str(text_file_path)


@pytest.fixture(scope='function')
def term(executable_path, temporary_text_file):
    with Runner(executable_path, temporary_text_file, width=COLS, height=ROWS) as r:
        yield r
        r.press('q')


def screenshot_to_lines(screenshot, substring):
    lines = [line for line in screenshot.split('\n') if substring in line]
    assert len(lines) <= TEXT_ROWS
    return lines


@pytest.mark.skipif(sys.version_info[:2] == (3, 4), reason='hack for travis')
@pytest.mark.parametrize('lines', [['X'*COLS*2 for _ in range(ROWS*2)]])
def test_window_size(term, lines):
    term.await_text(lines[0])
    screenshot = term.screenshot()
    assert screenshot.count('X') == (ROWS - 2) * COLS


def step_down(term):
    for _ in range(TEXT_ROWS):
        term.press('Down')


@pytest.mark.skipif(sys.version_info[:2] == (3, 4), reason='hack for travis')
@pytest.mark.parametrize('lines', [['line {}'.format(i) for i in range(TEXT_ROWS*2)]])
def test_step_down(term, lines):
    term.await_text(lines[TEXT_ROWS-1])
    screenshot = screenshot_to_lines(term.screenshot(), 'line')
    assert lines[TEXT_ROWS] not in screenshot
    step_down(term)
    term.await_text(lines[TEXT_ROWS])
    screenshot = screenshot_to_lines(term.screenshot(), 'line')
    assert lines[0] not in screenshot
    assert lines[TEXT_ROWS] == screenshot[-1]
    assert lines[TEXT_ROWS+1] not in screenshot


@pytest.mark.skipif(sys.version_info[:2] == (3, 4), reason='hack for travis')
@pytest.mark.parametrize('lines', [['line {}'.format(i) for i in range(TEXT_ROWS*2)]])
def test_multiple_steps_down(term, lines):
    for _ in range(TEXT_ROWS*2+7):
        term.press('Down')
    term.await_text(lines[-1])
    screenshot = screenshot_to_lines(term.screenshot(), 'line')
    assert len(lines[-TEXT_ROWS:]) == len(screenshot)
    assert lines[-TEXT_ROWS:] == screenshot


@pytest.mark.skipif(sys.version_info[:2] == (3, 4), reason='hack for travis')
@pytest.mark.parametrize('steps', [1, 5])
@pytest.mark.parametrize('lines', [['line {}'.format(i) for i in range(TEXT_ROWS*2)]])
def test_steps_up(term, lines, steps):
    step_down(term)
    for _ in range(TEXT_ROWS-1):
        term.press('Up')
    for _ in range(steps):
        term.press('Up')
    term.await_text(lines[0])
    screenshot = screenshot_to_lines(term.screenshot(), 'line')
    assert lines[TEXT_ROWS-1] == screenshot[-1]
    assert lines[TEXT_ROWS] not in screenshot


@pytest.mark.skipif(sys.version_info[:2] == (3, 4), reason='hack for travis')
@pytest.mark.parametrize('lines', [['line {}'.format(i) for i in range(TEXT_ROWS*3)]])
def test_page_down(term, lines):
    term.await_text(lines[TEXT_ROWS-1])
    screenshot = screenshot_to_lines(term.screenshot(), 'line')
    assert lines[TEXT_ROWS] not in screenshot
    term.press('PageDown')
    term.await_text(lines[TEXT_ROWS*2-1])
    screenshot = screenshot_to_lines(term.screenshot(), 'line')
    assert lines[TEXT_ROWS*2] not in screenshot


@pytest.mark.skipif(sys.version_info[:2] == (3, 4), reason='hack for travis')
@pytest.mark.parametrize('lines', [['line {}'.format(i) for i in range(TEXT_ROWS*3)]])
def test_multiple_pages_down(term, lines):
    term.await_text(lines[TEXT_ROWS-1])
    screenshot = screenshot_to_lines(term.screenshot(), 'line')
    assert lines[TEXT_ROWS] not in screenshot
    for _ in range(4):
        term.press('PageDown')
    term.await_text(lines[TEXT_ROWS*3-1])
    screenshot = screenshot_to_lines(term.screenshot(), 'line')
    assert lines[TEXT_ROWS*2-1] not in screenshot


@pytest.mark.skipif(sys.version_info[:2] == (3, 4), reason='hack for travis')
@pytest.mark.parametrize('pages', [1, 5])
@pytest.mark.parametrize('lines', [['line {}'.format(i) for i in range(TEXT_ROWS*3)]])
def test_page_down(term, lines, pages):
    term.await_text(lines[TEXT_ROWS-1])
    term.press('PageDown')
    term.await_text(lines[TEXT_ROWS*2-1])
    for _ in range(pages):
        term.press('PageUp')
    term.await_text(lines[TEXT_ROWS-1])
    screenshot = screenshot_to_lines(term.screenshot(), 'line')
    assert lines[0] in screenshot
    assert lines[TEXT_ROWS] not in screenshot


@pytest.mark.skipif(sys.version_info[:2] == (3, 4), reason='hack for travis')
@pytest.mark.parametrize('lines', [['line {}'.format(i) for i in range(TEXT_ROWS*3)]])
def test_text_end(term, lines):
    term.await_text(lines[TEXT_ROWS-1])
    term.press('M->')
    term.await_text(lines[TEXT_ROWS*3-1])
    screenshot = screenshot_to_lines(term.screenshot(), 'line')
    assert lines[TEXT_ROWS*2-1] not in screenshot
    assert lines[TEXT_ROWS*2] in screenshot
    for _ in range(TEXT_ROWS):
        term.press('Up')
    term.await_text(lines[TEXT_ROWS*3-2])
    screenshot = screenshot_to_lines(term.screenshot(), 'line')
    assert lines[TEXT_ROWS*3-1] not in screenshot


@pytest.mark.skipif(sys.version_info[:2] == (3, 4), reason='hack for travis')
@pytest.mark.parametrize('lines', [['line {}'.format(i) for i in range(TEXT_ROWS*3)]])
def test_text_begin(term, lines):
    term.await_text(lines[TEXT_ROWS-1])
    term.press('M->')
    term.await_text(lines[TEXT_ROWS*3-1])
    term.press('M-<')
    term.await_text(lines[TEXT_ROWS-1])
    screenshot = screenshot_to_lines(term.screenshot(), 'line')
    assert lines[0] in screenshot
    assert lines[TEXT_ROWS] not in screenshot
