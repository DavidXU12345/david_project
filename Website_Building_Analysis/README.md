Website is deployed with Netlify Drop. Link is **https://upbeat-gates-057053.netlify.app/**. It can show vistor's IP address through fetching API through ipify

I also installed Google Analytics using tracking code. I intentionally put Google Analytics tracking code below ipify's api javascript so that if I try to track click of `<code>` element, this specific `<code>` block will not fire any event but all other `<code>` block below Google Analytics tracking code can fire the event.

I also used Python code to analyze websites (e.g. search visible text and find subdomains).