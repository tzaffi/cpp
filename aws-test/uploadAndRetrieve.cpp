#include <aws/s3/S3Client.h>
#include <aws/s3/model/PutObjectRequest.h>
#include <aws/s3/model/GetObjectRequest.h>
#include <aws/core/Aws.h>
#include <aws/core/utils/memory/stl/AwsStringStream.h> 

using namespace Aws::S3;
using namespace Aws::S3::Model;
using namespace Aws::Client;
using namespace Aws::Auth;

static const char* KEY = "this_is_my_key"; //"s3_cpp_sample_key";
static const char* BUCKET = "tzaffi-cpp"; //"s3-cpp-sample-bucket";

int main()
{
    Aws::SDKOptions options;
    Aws::InitAPI(options);

    // Create a client
    ClientConfiguration config;
    config.scheme = Aws::Http::Scheme::HTTPS;
    // config.connectTimeoutMs = 30000;
    // config.requestTimeoutMs = 30000;
    // config.readRateLimiter = m_limiter;
    // config.writeRateLimiter = m_limiter;
    
    //S3Client client;
    AWSCredentials creds("AKIAJSX3GKH3SC4VE6OQ","fBfm6kIA3Ejqg2ElsTZssRQUn309DZqFNeynskwL");
    auto client = Aws::MakeShared<S3Client>("tzaffi", creds, config); 
    //first put an object into s3
    PutObjectRequest putObjectRequest;
    putObjectRequest.WithKey(KEY)
           .WithBucket(BUCKET);

    //this can be any arbitrary stream (e.g. fstream, stringstream etc...)
    auto requestStream = Aws::MakeShared<Aws::StringStream>("s3-sample");
    *requestStream << "Hello World!";
    
    //set the stream that will be put to s3
    putObjectRequest.SetBody(requestStream);

    auto putObjectOutcome = client.PutObject(putObjectRequest);

    if(putObjectOutcome.IsSuccess())
    {
        std::cout << "Put object succeeded" << std::endl;
    }
    else
    {
        std::cout << "Error while putting Object " << putObjectOutcome.GetError().GetExceptionName() << 
               " " << putObjectOutcome.GetError().GetMessage() << std::endl;
    }

    //now get the object back out of s3. The response stream can be overridden here if you want it to go directly to 
    // a file. In this case the default string buf is exactly what we want.
    GetObjectRequest getObjectRequest;
    getObjectRequest.WithBucket(BUCKET)
        .WithKey(KEY);

    auto getObjectOutcome = client.GetObject(getObjectRequest);

    if(getObjectOutcome.IsSuccess())
    {
        std::cout << "Successfully retrieved object from s3 with value: " << std::endl;
        std::cout << getObjectOutcome.GetResult().GetBody().rdbuf() << std::endl << std::endl;;  
    }
    else
    {
        std::cout << "Error while getting object " << getObjectOutcome.GetError().GetExceptionName() <<
             " " << getObjectOutcome.GetError().GetMessage() << std::endl;
    }

    Aws::ShutdownAPI(options);
    return 0;  
}
