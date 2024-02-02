import os
import re
import argparse

class MarkdownLinkChecker:
    def __init__(self, markdown_path):
        self.markdown_path = markdown_path

    def is_valid_link(self, link):
        # Ignore links starting with "http" as they are assumed to be external URLs
        return link.startswith('http') or os.path.exists(link)

    def check_markdown_links(self):
        invalid_links = []

        with open(self.markdown_path, 'r', encoding='utf-8') as file:
            content = file.read()

        # Use a regular expression to find all the links in the markdown file
        link_pattern = re.compile(r'\[.*?\]\((.*?)\)')
        matches = link_pattern.findall(content)

        for link in matches:
            if not self.is_valid_link(link):
                invalid_links.append(link)

        return invalid_links

def main():
    parser = argparse.ArgumentParser(description='Check validity of links in a Markdown file.')
    parser.add_argument('markdown_file', help='Path to the Markdown file to check.')

    args = parser.parse_args()

    markdown_link_checker = MarkdownLinkChecker(args.markdown_file)
    invalid_links = markdown_link_checker.check_markdown_links()

    if invalid_links:
        print("Invalid links found:")
        for link in invalid_links:
            print(link)
        exit(1)
    else:
        print("All links are valid.")

if __name__ == "__main__":
    try:
        main()
    except argparse.ArgumentError:
        print("Error: Please provide the path to the Markdown file.")
