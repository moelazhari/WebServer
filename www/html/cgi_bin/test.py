#!/usr/bin/env python
"""Very basic Python script that outputs static HTML content."""

import cgi


def template():
    """Returns the a formatted templated. This can be placed in an HTML file."""
    templ = """
<html>
<title>{title}</title>
<body>
  Hello, {username}!
</body>
</html>
            """
    return templ


def render(**kwargs):
    content = template().format(**kwargs)
    print(content)


def run():
    username = 'Kanat'
    title = 'My first tinyPy.cgi'
    render(**locals())


if __name__ == '__main__':
    try:
        # Tell the browser it's an HTML page.
        print('Content-Type: text/html\r\n')
        # print('\r\n')
        # Main program.
        run()
    except:
        cgi.print_exception()