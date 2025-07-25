# Hash Prompts Installer for Windows
# This script installs Hash Prompts as Claude commands with /#: prefix
# Repository: https://github.com/dimitritholen/prompts

# Ensure script stops on errors
$ErrorActionPreference = "Stop"

# GitHub repository information
$RepoOwner = "dimitritholen"
$RepoName = "prompts"
$Branch = "main"
$BaseUrl = "https://raw.githubusercontent.com/$RepoOwner/$RepoName/$Branch"

# Prompt files to install
$Prompts = @(
    "brainstorm.md",
    "prd.md",
    "architect.md",
    "tasks.md",
    "plan.md",
    "code.md",
    "feature.md",
    "test.md",
    "deploy.md",
    "pipeline.md",
    "generate-agent.md",
    "help.md"
)

# Module files to install
$Modules = @(
    "modules/common.inc",
    "modules/research.inc",
    "modules/slc-validation.inc",
    "modules/agent-generation.inc",
    "modules/handoffs.inc",
    "modules/README.inc"
)

# Function to print colored output
function Write-ColorOutput {
    param(
        [string]$Message,
        [string]$ForegroundColor = "White"
    )
    Write-Host $Message -ForegroundColor $ForegroundColor
}

# Function to print header
function Show-Header {
    Write-Host ""
    Write-ColorOutput "════════════════════════════════════════════════════" -ForegroundColor Blue
    Write-ColorOutput "       Hash Prompts (#) Installer" -ForegroundColor Blue
    Write-ColorOutput "════════════════════════════════════════════════════" -ForegroundColor Blue
    Write-Host ""
}

# Function to check if Claude CLI is installed
function Test-ClaudeCLI {
    try {
        $null = Get-Command claude -ErrorAction Stop
        Write-ColorOutput "✓ Claude CLI detected" -ForegroundColor Green
        return $true
    } catch {
        Write-ColorOutput "❌ Claude CLI is not installed!" -ForegroundColor Red
        Write-ColorOutput "Please install Claude Code first: https://claude.ai/code" -ForegroundColor Yellow
        return $false
    }
}

# Function to prompt for installation type
function Get-InstallLocation {
    Write-Host ""
    Write-ColorOutput "Where would you like to install the commands?" -ForegroundColor Yellow
    Write-Host "1) Global (available in all projects) - ~/.claude/commands [default]"
    Write-Host "2) Local (current project only) - ./.claude/commands"
    Write-Host ""
    
    # Check if running interactively
    if ([Environment]::UserInteractive -and -not [Environment]::GetCommandLineArgs().Contains("-NonInteractive")) {
        $choice = Read-Host "Enter your choice (1 or 2) [1]"
    } else {
        Write-ColorOutput "Running in non-interactive mode, defaulting to global installation" -ForegroundColor Blue
        $choice = "1"
    }
    
    # Default to option 1 if empty
    if ([string]::IsNullOrWhiteSpace($choice)) {
        $choice = "1"
    }
    
    switch ($choice) {
        "1" {
            $script:InstallDir = Join-Path $env:USERPROFILE ".claude\commands"
            $script:InstallType = "global"
        }
        "2" {
            $script:InstallDir = Join-Path (Get-Location) ".claude\commands"
            $script:InstallType = "local"
        }
        default {
            Write-ColorOutput "Invalid choice. Exiting." -ForegroundColor Red
            exit 1
        }
    }
    
    Write-ColorOutput "→ Installing to: $InstallDir" -ForegroundColor Green
}

# Function to create directory structure
function New-Directories {
    Write-ColorOutput "Creating directory structure..." -ForegroundColor Blue
    
    $namespaceDir = Join-Path $InstallDir "#"
    if (!(Test-Path -Path $namespaceDir)) {
        New-Item -ItemType Directory -Path $namespaceDir -Force | Out-Null
    }
    
    $modulesDir = Join-Path $namespaceDir "modules"
    if (!(Test-Path -Path $modulesDir)) {
        New-Item -ItemType Directory -Path $modulesDir -Force | Out-Null
    }
    
    Write-ColorOutput "✓ Directories created" -ForegroundColor Green
}

# Function to download and install a prompt
function Install-Prompt {
    param(
        [string]$PromptFile
    )
    
    $commandName = [System.IO.Path]::GetFileNameWithoutExtension($PromptFile)
    $sourceUrl = "$BaseUrl/$PromptFile"
    $destFile = Join-Path $InstallDir "#\$commandName.md"
    
    Write-ColorOutput "Installing /#:$commandName..." -ForegroundColor Blue
    
    try {
        # Download the prompt file
        $tempFile = [System.IO.Path]::GetTempFileName()
        Invoke-WebRequest -Uri $sourceUrl -OutFile $tempFile -UseBasicParsing
        
        # Read the downloaded content
        $promptContent = Get-Content -Path $tempFile -Raw
        
        # Create Claude command format
        $commandContent = @"
# /#:$commandName Command

This command activates the $commandName mode for your AI assistant.

Usage: /#:$commandName `$ARGUMENTS

---

$promptContent
"@
        
        # Write the command file
        Set-Content -Path $destFile -Value $commandContent -Encoding UTF8
        
        # Clean up temp file
        Remove-Item -Path $tempFile -Force
        
        Write-ColorOutput "✓ Installed /#:$commandName" -ForegroundColor Green
        return $true
    } catch {
        Write-ColorOutput "❌ Failed to download $PromptFile" -ForegroundColor Red
        Write-ColorOutput $_.Exception.Message -ForegroundColor Red
        return $false
    }
}

# Function to install all prompts
function Install-AllPrompts {
    Write-ColorOutput "`nInstalling Hash Prompts commands..." -ForegroundColor Blue
    
    $installed = 0
    $failed = 0
    
    foreach ($prompt in $Prompts) {
        if (Install-Prompt -PromptFile $prompt) {
            $installed++
        } else {
            $failed++
        }
    }
    
    Write-Host ""
    Write-ColorOutput "✓ Successfully installed: $installed commands" -ForegroundColor Green
    if ($failed -gt 0) {
        Write-ColorOutput "⚠ Failed to install: $failed commands" -ForegroundColor Yellow
    }
}

# Function to download and install a module
function Install-Module {
    param(
        [string]$ModuleFile
    )
    
    $moduleName = Split-Path -Leaf $ModuleFile
    $sourceUrl = "$BaseUrl/$ModuleFile"
    $destFile = Join-Path $InstallDir "#" $ModuleFile
    
    Write-ColorOutput "Installing module: $moduleName..." -ForegroundColor Blue
    
    try {
        # Download the module file
        $webClient = New-Object System.Net.WebClient
        $webClient.DownloadFile($sourceUrl, $destFile)
        Write-ColorOutput "✓ Installed module: $moduleName" -ForegroundColor Green
        return $true
    } catch {
        Write-ColorOutput "❌ Failed to download $ModuleFile" -ForegroundColor Red
        return $false
    }
}

# Function to install all modules
function Install-AllModules {
    Write-Host ""
    Write-ColorOutput "Installing modules..." -ForegroundColor Blue
    
    $installed = 0
    $failed = 0
    
    foreach ($module in $Modules) {
        if (Install-Module -ModuleFile $module) {
            $installed++
        } else {
            $failed++
        }
    }
    
    Write-Host ""
    Write-ColorOutput "✓ Successfully installed: $installed modules" -ForegroundColor Green
    if ($failed -gt 0) {
        Write-ColorOutput "⚠ Failed to install: $failed modules" -ForegroundColor Yellow
    }
}

# Function to show usage instructions
function Show-Usage {
    Write-Host ""
    Write-ColorOutput "════════════════════════════════════════════════════" -ForegroundColor Blue
    Write-ColorOutput "✨ Installation Complete!" -ForegroundColor Green
    Write-ColorOutput "════════════════════════════════════════════════════" -ForegroundColor Blue
    Write-Host ""
    Write-ColorOutput "Available Commands:" -ForegroundColor Yellow
    
    foreach ($prompt in $Prompts) {
        $commandName = [System.IO.Path]::GetFileNameWithoutExtension($prompt)
        Write-Host "  /#:$commandName"
    }
    
    Write-Host ""
    Write-ColorOutput "Usage Examples:" -ForegroundColor Yellow
    Write-Host "  /#:brainstorm I want to build a task management app"
    Write-Host "  /#:architect Design a microservices architecture"
    Write-Host "  /#:generate-agent Qiskit 2026 quantum"
    Write-Host "  /#:pipeline start"
    Write-Host ""
    
    Write-ColorOutput "✓ Modular Architecture:" -ForegroundColor Green
    Write-Host "  Shared patterns are now in modules/ for better maintainability"
    Write-Host ""
    
    if ($InstallType -eq "local") {
        Write-ColorOutput "Note: These commands are only available in this project." -ForegroundColor Blue
    } else {
        Write-ColorOutput "Note: These commands are available globally in all projects." -ForegroundColor Blue
    }
    Write-Host ""
}

# Function to check execution policy
function Test-ExecutionPolicy {
    $policy = Get-ExecutionPolicy -Scope CurrentUser
    if ($policy -eq "Restricted") {
        Write-ColorOutput "⚠ PowerShell execution policy is restricted." -ForegroundColor Yellow
        Write-ColorOutput "To run this script, you may need to run:" -ForegroundColor Yellow
        Write-ColorOutput "Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser" -ForegroundColor Cyan
        Write-Host ""
        
        $continue = Read-Host "Do you want to continue anyway? (y/n)"
        if ($continue.ToLower() -ne "y") {
            exit 1
        }
    }
}

# Main installation flow
function Start-Installation {
    Show-Header
    Test-ExecutionPolicy
    
    if (!(Test-ClaudeCLI)) {
        exit 1
    }
    
    Get-InstallLocation
    New-Directories
    Install-AllPrompts
    Install-AllModules
    Show-Usage
}

# Run the installation
try {
    Start-Installation
    exit 0
} catch {
    Write-ColorOutput "❌ An error occurred during installation" -ForegroundColor Red
    Write-ColorOutput $_.Exception.Message -ForegroundColor Red
    exit 1
}