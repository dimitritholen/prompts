#!/bin/bash
# Test script for quiet mode pipeline

echo "=== Testing Pipeline Quiet Mode ==="
echo ""
echo "1. Normal mode (verbose output):"
echo "--------------------------------"
bash -c '/#:pipeline start'

echo ""
echo ""
echo "2. Quiet mode (minimal output):"
echo "-------------------------------"
bash -c '/#:pipeline start --quiet'

echo ""
echo ""
echo "3. Verbose mode (debug output):"
echo "-------------------------------"
bash -c '/#:pipeline start --verbose'