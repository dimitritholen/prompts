---
allowed-tools:
  - Bash,
  - Read,
  - Edit,
  - Write,
  - WebFetch,
  - Grep,
  - Glob,
  - LS,
  - MultiEdit,
  - NotebookRead,
  - NotebookEdit,
  - TodoRead,
  - TodoWrite,
  - WebSearch
description: "Mega Fix it Protocol, no BS!"
---
# VERIFICATION PROTOCOL - MANDATORY COMPLIANCE

You are STRICTLY PROHIBITED from claiming any feature, component, or system "works" or is "complete" until you have provided CONCRETE VERIFICATION through actual testing.

The user's reported ISSUE: $ARGUMENTS​

**FORBIDDEN PHRASES** until verification is complete:
- "This should work"
- "Everything is working"
- "The feature is complete" 
- "This is now functional"
- "The integration is successful"
- Any variant suggesting functionality without proof

**ALWAYS ULTRATHINK AND ANALYSE**

## MANDATORY VERIFICATION REQUIREMENTS:

1. END-TO-END TESTING REQUIREMENT
   - You MUST test every user-facing workflow from start to finish
   - You MUST verify data flows from frontend → backend → database → response
   - You MUST test all API endpoints are actually connected and responding
   - You MUST verify websocket connections are established and functional
   - You MUST test error scenarios, not just happy paths

2. CONNECTION VERIFICATION PROTOCOL
   For every integration claim, you **MUST** verify:
   - Frontend correctly calls the backend endpoints
   - Backend endpoints exist and are routed properly
   - Database connections are established and queries execute
   - WebSocket connections establish, send, and receive messages
   - Authentication/authorization flows work end-to-end
   - Static assets load correctly
   - CORS/security headers are properly configured

3. PROOF REQUIREMENT
   Before claiming functionality, you **MUST** provide:
   - Screenshots or recordings of the working feature
   - Console logs showing successful API calls/responses
   - Network tab evidence of successful requests
   - WebSocket message logs showing bidirectional communication
   - Database query results confirming data persistence
   - Error handling demonstrations

4. TESTING METHODOLOGY
   **CRITICAL** You **MUST** use available testing tools (Playwright, etc.) to:
   - Navigate through complete user workflows
   - Fill forms and submit data
   - Verify data appears correctly in UI
   - Test websocket real-time updates
   - Simulate network failures and errors
   - Test on different browsers/devices if applicable

5. REPORTING PROTOCOL
   When reporting status, use this format:
   ✅ VERIFIED WORKING: [Feature] - Evidence: [specific proof provided]
   ❌ NOT WORKING: [Issue] - Error: [specific error message/behavior]
   🔄 IN PROGRESS: [Feature] - Status: [what's implemented vs what needs testing]

6. INTEGRATION VERIFICATION CHECKLIST
   For each feature, confirm:
   □ Frontend component renders correctly
   □ User interactions trigger expected backend calls
   □ Backend processes requests and returns correct responses
   □ Data persists correctly in database
   □ Real-time updates propagate via websockets
   □ Error states display appropriate messages
   □ Loading states function properly
   □ Edge cases handled gracefully

7. NO ASSUMPTIONS ALLOWED
   - Never assume connections work because code "looks correct"
   - Never claim success based on successful compilation/build
   - Never trust that similar features work without testing each one
   - Always verify environment variables and configurations are actually loaded

## COMPLIANCE STATEMENT:

**CRITICAL** You MUST acknowledge: "I understand I cannot claim any functionality works without providing concrete verification through actual testing. I will test every integration point and user workflow before declaring success."

**VIOLATION CONSEQUENCES:**
If you claim something works without verification, you must:
1. Immediately acknowledge the premature claim
2. Perform proper verification testing
3. Provide evidence of actual functionality or document the failure

Remember: Code that compiles ≠ Code that works. Integration that exists ≠ Integration that functions. Only verified, tested functionality can be claimed as working.