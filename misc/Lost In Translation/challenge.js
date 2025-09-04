import fetch from 'node-fetch';			  		
	
import readlineSync from 'readline-sync';  			 			
	
async function translateText(text, targetLanguage) { 		    	
	
    const params	=	new URLSearchParams(		 	
	
     	{		    
	
     	    q:text,		
	
     	 	langpair:`en|${targetLanguage}` 	  
	
     	}   		 
	);
    try {				 		
	
     	const response=await	fetch(`https://api.mymemory.translated.net/get?${params}`); 			
	
     	const	data =	await response.json();  
	
     	return	data.responseData.translatedText; 	  	
	
    } catch(error){console.error("Translation error:", error);}			 	  
	
    return null;		
}	
 	    
	
 	   			 	 	
	
async function main() {  			 	  
	
    const text=readlineSync.question(`	 					
	
Enter the text to translate: 	 	 			
	
`);      
	
 	const targetLanguage=readlineSync.question(`  			  	 
	
Enter target language ('en'-English, 'fr'-French, etc.)		 	 		
	
`);     	 	
	
 	const translatedText=await translateText(text, targetLanguage);	 					
	
    if (translatedText)	{ 	 			
	
      
	
 	   	console.log(`Translation:	${translatedText}`); 			 
	
    } else	{	  	  
	
     	console.log('Translation	Lost!');
	}
} 	   			  	 
	
     	 	
	
 	   					 	
	
  

main();
