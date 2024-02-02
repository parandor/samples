import os
import re
import argparse

class MarkdownLinkChecker:
    def __init__(self, markdown_path):
        self.markdown_path = markdown_path
        self.directory_path = os.path.join(os.path.dirname(markdown_path), '')

    def is_valid_link(self, link):
        # Ignore links starting with "http" as they are assumed to be external URLs
        if link.startswith('http') or link.startswith('\\'):
            return True
        # Ignore links if they exist, and prepend path to readme 
        return os.path.exists(self.directory_path + link)

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

def check_all_readme_files(directory):
    invalid_links = []

    for root, dirs, files in os.walk(directory):
        for file in files:
            if file.lower() == 'readme.md':
                readme_path = os.path.join(root, file)
                markdown_link_checker = MarkdownLinkChecker(readme_path)
                invalid_links.extend(markdown_link_checker.check_markdown_links())

    return invalid_links

def main():
    parser = argparse.ArgumentParser(description='Check validity of links in all README.md files in a directory.')
    parser.add_argument('directory', help='Path to the directory containing README.md files.')

    args = parser.parse_args()

    invalid_links = check_all_readme_files(args.directory)

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
        print("Error: Please provide the path to the directory containing README.md files.")
