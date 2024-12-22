1. Install Git
    Download and Install: Begin by downloading the latest version of Git from the official website or using a package manager for your OS. For Windows, you can use the Git installer, while macOS users can install it via Homebrew with brew install git. Linux users can typically install it using their distribution’s package manager (e.g., sudo apt install git for Ubuntu)

2. Configure Git
    Set Up User Information: After installation, configure your Git environment by setting your username and email, which will be associated with your commits:
    ```bash
    git config --global user.name "Your Name"
    git config --global user.email "your.email@example.com"
    ```

    Check Configuration: You can view your settings with:
    ```bash
    git config --list
    ```

3. Create a Repository
    Initialize a New Repository: Navigate to your project directory and run:
    ```bash
    git init
    ```

    This command creates a new Git repository in that directory
    Clone an Existing Repository: If you want to work on an existing project, you can clone it using:
    ```bash
    git clone <repository-url>
    ```

    Replace <repository-url> with the URL of the repository you want to clone

4. Basic Commands
    Check Status: To see the status of your files (tracked, untracked, modified):
    ```bash
    git status
    ```

    Add Files to Staging: Before committing changes, you need to stage them:
    ```bash
    git add <file-name>   # Add a specific file
    git add .             # Add all changes in the current directory
    ```

    Commit Changes: After staging, commit your changes with a descriptive message:
    ```bash
    git commit -m "Your commit message"
    ```

5. Working with Branches
    Create a New Branch: To create and switch to a new branch:
    ```bash
    git checkout -b <branch-name>
    ```

    Switch Branches: To switch back to an existing branch:
    ```bash
    git checkout <branch-name>
    ```

6. Pushing Changes
    After making changes locally, push them to a remote repository (e.g., on GitHub):
    ```bash
    git push origin <branch-name>
    ```

7. Pulling Changes
    To update your local repository with changes from the remote repository:
    ```bash
    git pull origin <branch-name>
    ```
