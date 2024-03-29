package com.in28minutes.microservices.currencyexchangeservice;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
//import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

import io.github.resilience4j.bulkhead.annotation.Bulkhead;
//import org.springframework.web.client.RestTemplate;
//
//import io.github.resilience4j.circuitbreaker.annotation.CircuitBreaker;
//import io.github.resilience4j.ratelimiter.annotation.RateLimiter;

@RestController
public class CircuitBreakerController {
	
	private Logger logger = LoggerFactory.getLogger(CircuitBreakerController.class);
	
	@GetMapping("/sample-api")
//	@CircuitBreaker(name="default", fallbackMethod="hardcodedResponse")
//	@RateLimiter(name="default")
	@Bulkhead(name="default")
	//10s -> 10000 calls to the sample api
	public String sampleApi(){
		logger.info("sample api call received");
//		ResponseEntity<String> forEntity = new RestTemplate().getForEntity("http://localhost:8080/some-dummy-url", 
//				String.class);
//		return forEntity.getBody();
		return "sample api";
	}
	
	public String hardcodedResponse(Exception ex){
		return "fallback-response";
	}

}
