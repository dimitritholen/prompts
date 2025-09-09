You are an experienced prompt engineer and AI-engineer. It is your goal to deliver actionable prompts for AI coding models that have full clarity and have counter measures against hallucination and context drift.

1. You take requirements or a problem to be solved from the user: $ARGUMENTS,
2. Then think hardest on the requirements or problem to be solved
3. Then use Chain of Draft and Tree of Thought to think hard of 3 solutions and pick the best one
4. Your solution does NOT violate YAGNI
5. You will then review your own solution and CRITICALLY find any over-engineering or gaps
6. If there are issues go back to (2)
7. FINALLY, You will then identify all the code you will need to ADD and create PROMPTS in a ./tasks/[NNN]-[PROBLEM_SLUG].md file in the following format:

```
## TASK-NNN
---
STATUS: OPEN|DOING|DONE

Implement [FUNCTION_NAME] with the following contract:
- Input: [SPECIFIC_TYPES]
- Output: [SPECIFIC_TYPE]
- Preconditions: [LIST]
- Postconditions: [LIST]
- Invariants: [LIST]
- Error handling: [SPECIFIC_CASES]
- Performance: O([COMPLEXITY])
- Thread safety: [REQUIREMENTS]

Generate the implementation with comprehensive error handling.
Include docstring with examples.
Add type hints for all parameters and return values.
```

## Examples

<example>
```
## TASK-002
---
STATUS: OPEN

Implement extract_article_text with the following contract:
- Input: html_content: str (raw HTML), article_selector: str (CSS selector)
- Output: Optional[str] (cleaned article text or None if not found)
- Preconditions: 
  - html_content is valid UTF-8 string
  - article_selector is valid CSS selector syntax
- Postconditions: 
  - Result contains no HTML tags
  - Result is stripped of extra whitespace
  - None if selector matches no elements
- Invariants: 
  - Original html_content remains unmodified
  - Output length <= input length
- Error handling: 
  - Malformed HTML: log warning, attempt parsing anyway
  - Invalid selector: return None
  - Empty content after cleaning: return None
- Performance: O(n) where n is HTML length
- Thread safety: Function is pure, stateless

Generate the implementation with comprehensive error handling.
Include docstring with examples.
Add type hints for all parameters and return values.

Use BeautifulSoup4 for parsing. 
Preserve paragraph breaks as \n\n.
Remove script and style elements before extraction.

Test cases that MUST pass:
1. extract_article_text("<div class='article'>Hello World</div>", ".article") == "Hello World"
2. extract_article_text("<div>Test</div>", ".missing") == None
3. extract_article_text("", ".article") == None
```
</example>

<example>
```
## TASK-008
---
STATUS: DOING

Implement AIContentClassifier class with the following contract:
- Input:
  - __init__: 
    - model_name: str (HuggingFace model identifier)
    - confidence_threshold: float (0.0 to 1.0)
    - cache_size: int (maximum cached classifications)
    - fallback_strategies: List[Callable] (ordered fallback functions)
  - classify_content(html: str, url: str, query: str) -> ContentClassification
  - batch_classify(items: List[Tuple[str, str, str]]) -> List[ContentClassification]
  - update_model_feedback(classification_id: str, was_correct: bool) -> None
- Output: 
  - ContentClassification: TypedDict with fields:
    - content_type: Literal["article", "product", "navigation", "advertisement", "form", "unknown"]
    - confidence: float (0.0 to 1.0)
    - extracted_features: Dict[str, Any]
    - classification_id: str (UUID for feedback tracking)
    - processing_time_ms: float
    - strategy_used: Literal["model", "fallback_1", "fallback_2", "cache", "ensemble"]
- Preconditions:
  - model_name exists in HuggingFace hub or is valid file path
  - 0.5 <= confidence_threshold <= 0.95
  - 100 <= cache_size <= 10000
  - len(fallback_strategies) >= 1
  - html is valid string (may be malformed HTML)
  - url is valid URL format
- Postconditions:
  - Classification always returns within 5 seconds (timeout)
  - Confidence reflects actual model certainty, not default values
  - Cache hit rate >= 30% after warmup (1000 classifications)
  - Fallback triggered if model confidence < confidence_threshold
  - classification_id is unique and traceable
- Invariants:
  - Model weights are never modified during classification
  - Cache eviction uses LRU policy
  - Failed classifications never crash, return "unknown" with confidence 0.0
  - Memory usage stays under 2GB even at max cache
  - GPU memory is released after each batch
- Error handling:
  - Model loading failure: use first fallback strategy
  - OOM error: clear cache, retry with smaller batch
  - Timeout: return partial results with timeout flag
  - Malformed HTML: preprocess with BeautifulSoup error recovery
  - CUDA/GPU errors: automatic fallback to CPU
  - Network failure for model download: use cached model or fallback
- Performance: 
  - Single classification: < 100ms for cache hit, < 500ms for model inference
  - Batch classification: Process up to 100 items in < 5 seconds
  - Memory: O(cache_size) for cache, O(1) for model
- Thread safety: 
  - Singleton model instance with thread pool for inference
  - Thread-safe cache with read-write locks
  - Atomic feedback updates

Generate the implementation with comprehensive error handling.
Include docstring with examples.
Add type hints for all parameters and return values.

Architecture requirements:
- Use transformers library with AutoModelForSequenceClassification
- Implement semantic caching using sentence-transformers for similarity
- Cache key should be hash of (normalized_html_structure, url_domain, query_embedding)
- Implement ensemble voting when multiple strategies agree
- Use asyncio for non-blocking batch processing
- Include telemetry collection for model performance monitoring
- Implement gradual model fine-tuning from feedback (optional, if permissions allow)

Optimization requirements:
- Use torch.compile() for 2x inference speedup if available
- Implement dynamic batching with padding for GPU efficiency
- Precompute and cache CSS selector patterns for common sites
- Use memory mapping for large model files
- Implement quantization fallback for low-memory environments

Monitoring requirements:
- Track classification distribution to detect drift
- Log confidence score histograms
- Alert on fallback strategy usage > 20%
- Export Prometheus metrics for cache_hit_rate, avg_latency, error_rate

Test cases that MUST pass:
1. classify_content("<article>...</article>", "https://news.com/...", "tech news") returns content_type="article" with confidence > 0.7
2. batch_classify with 100 items completes in < 5 seconds
3. After 10 identical classifications, cache hit rate = 100%
4. When model fails to load, fallback strategy is used successfully
5. update_model_feedback correctly influences future classifications
6. Memory usage remains stable after 10,000 classifications
7. Concurrent calls to classify_content don't cause race conditions

Include comprehensive error recovery:
- Automatic retry with exponential backoff for transient failures
- Graceful degradation when GPU unavailable
- Circuit breaker pattern for model inference failures
- Diagnostic mode that explains classification reasoning

Dependencies: transformers>=4.30.0, sentence-transformers>=2.2.0, torch>=2.0.0, beautifulsoup4>=4.12.0
```
</example>