#include "JsonHandler.h"

QMutex JsonHandler::mutex; // Initialize the static mutex

JsonHandler::JsonHandler() {}

bool JsonHandler::CheckUserFound(const QString &fileName, const QString &UserName)
{
    // Lock the Mutex
    QMutexLocker locker(&mutex);
    bool IsFound = false;
    //set file
    QFile file(fileName);
    // Open file as text and read contents
    if ( file.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        // Read all file and save it as json Document
        QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll());
        file.close();
        // Check if Document contains valid json data && the structure is an object
        if (!jsonDoc.isNull() && jsonDoc.isObject())
        {
            // Turn the json Doc to a json object to deal with it as json object
            QJsonObject jsonObject = jsonDoc.object();

            //Check if Specified object exists
            if (jsonObject.contains(UserName))
            {
                // UserName is found in Data base
                IsFound = true;
            }else
            {
                qDebug() << "UserName is not found";
                IsFound = false;
            }
        }else{
            qDebug() << "Failed to parse JSON Data from file";
            IsFound = false;
        }
    }else{
        qDebug() << "Failed to open file to read";
        IsFound = false;
    }
    return IsFound;
}

bool JsonHandler::CheckLogin(const QString &fileName, const QString &UserName, const QString &UsrPassword)
{
    // Set mutex for thread safety
    QMutexLocker locker(&mutex);
    // Set file to be able to use it as a file
    bool ok = false;
    QFile file(fileName);
    if ( file.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        // Read all file and save it as json Document
        QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll());
        file.close();
        // Check if Document contains valid json data && the structure is an object
        if (!jsonDoc.isNull() && jsonDoc.isObject())
        {
            // Turn the json Doc to a json object to deal with it as json object
            QJsonObject jsonObject = jsonDoc.object();

            //Check if Specified object exists
            if (jsonObject.contains(UserName))
            {
                // Get the specified object and turn it to json document
                QJsonObject TargetUser = jsonObject.value(UserName).toObject();
                //Get Password from the object
                QString Pass = TargetUser["Password"].toString();

                //Check if the password is the same
                if( UsrPassword == Pass)
                {
                    ok = true;
                }else
                {
                    qDebug() << "password dont match";
                    ok = false;
                }
            }else {
                qDebug() << "This user name is not found in the DataBase";
                ok = false;
            }
        } else{
            qDebug() << "Failed to parse JSON Data from file";
            ok = false;
        }
    }else {
        qDebug() << "Failed to open file to read";
        ok = false;
    }

    return ok;
}

bool JsonHandler::GetField(const QString &fileName, const QString &UserName, const QString &Field, QString &FieldValue)
{
    // Set mutex for thread safety
    QMutexLocker locker(&mutex);
    // Set file to be able to use it as a file
    bool ok = false;
    QFile file(fileName);
    if ( file.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        // Read all file and save it as json Document
        QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll());
        file.close();
        // Check if Document contains valid json data && the structure is an object
        if (!jsonDoc.isNull() && jsonDoc.isObject())
        {
            // Turn the json Doc to a json object to deal with it as json object
            QJsonObject jsonObject = jsonDoc.object();

            //Check if Specified object exists
            if (jsonObject.contains(UserName))
            {
                // Get the specified object and turn it to json document
                QJsonObject TargetUser = jsonObject.value(UserName).toObject();
                // Take value from field and set it into the argument
                FieldValue = TargetUser[Field].toString();
                ok = true;
            }else {
                qDebug() << "This user name is not found in the DataBase";
                ok = false;
            }
        }else {
            qDebug() << "Failed to parse JSON Data from file";
            ok = false;
        }
    }else {
        qDebug() << "Failed to open file to read";
        ok = false;
    }

    return ok;
}

bool JsonHandler::SetField(const QString &fileName, const QString &UserName, const QString &Field, const QString &NewValue)
{
    // Set mutex for thread safety
    QMutexLocker locker(&mutex);
    bool ok = false;
    // set file
    QFile file(fileName);
    // open file and read it
    if (file.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        //Parse the JSON document from the file
        QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll());
        file.close();
        // Check if the JSON document is an object
        if(!jsonDoc.isNull() && jsonDoc.isObject())
        {
            // Create a new json object and save the old json object in it
            QJsonObject jsonObj = jsonDoc.object();
            // Check if the specified object key exists and is an object
            if ( jsonObj.contains(UserName) && jsonObj[UserName].isObject() )
            {
                // Modify the new json object,, create new object from the original object
                QJsonObject TheNewObject = jsonObj[UserName].toObject();
                // set the new value to the object's field
                TheNewObject[Field] = NewValue;
                // Update the original json object in the main json file
                jsonObj[UserName] = TheNewObject ;
                // write the modifited json object to the main json file
                if( file.open(QIODevice::WriteOnly | QIODevice::Text) )
                {
                    // initialze a new json doc with the updated field value
                    QJsonDocument modifiedJsonDoc(jsonObj);
                    // write to the file to save the new json doc
                    file.write(modifiedJsonDoc.toJson());
                    file.close();
                    ok = true;
                }else {
                    qDebug() << "Error: Unable to open the file for writing.";
                    ok = false;
                }
            }else {
                qDebug() << "Error: Object key not found or not an object.";
                ok = false;
            }
        } else {
            qDebug() << "Error: Invalid JSON document.";
            ok = false;
        }
    }else {
        qWarning() << "Failed to open file for reading:" << file.errorString();
        ok = false;
    }
    return ok;
}

bool JsonHandler::PrintDataBase(const QString &fileName, QString &JsonDataBase)
{
    // Set mutex for thread safety
    QMutexLocker locker(&mutex);
    // Set file to be able to use it as a file
    bool ok = false;
    QFile file(fileName);
    if ( file.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        // Read all data from the file
        QByteArray jsonData = file.readAll();

        // Parse the JSON data
        QJsonDocument doc = QJsonDocument::fromJson(jsonData);

        // Check if the document is valid
        if (!doc.isNull())
        {
            // Convert JSON document to formatted string & save to variable
            JsonDataBase = doc.toJson(QJsonDocument::Indented);
            ok = true;
        }
        else
        {
            qDebug() << "Failed to parse JSON document";
            ok = false;
        }
    }else {
        qDebug() << "Failed to open file to read";
        ok = false;
    }
    return ok;
}

bool JsonHandler::DeleteUser(const QString &fileName, const QString &UserName)
{
    // Set mutex for thread safety
    QMutexLocker locker(&mutex);
    // Set file to be able to use it as a file
    bool ok = false;
    QFile file(fileName);
    if ( file.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        // Parse Json Doc
        QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll());
        file.close();
        //  Check if the JSON document is an object
        if (jsonDoc.isObject())
        {
            // Set json doc to a json object
            QJsonObject jsonObject = jsonDoc.object();
            // Check if the specified user name exists exists
            if (jsonObject.contains(UserName))
            {
                // Remove the specified object from the main JSON object
                jsonObject.remove(UserName);
                // Write the modified JSON object back to the file
                if (file.open(QIODevice::WriteOnly | QIODevice::Text))
                {
                    QJsonDocument NewJsonDoc(jsonObject);
                    file.write(NewJsonDoc.toJson());
                    file.close();
                    ok = true;
                } else
                    {
                        qDebug() << "Unable to open the file for writing.";
                        ok = false;
                    }
            } else
                {
                    qDebug() << "User Name is not found.";
                    ok = false;
                }
        } else
            {
            qDebug() << "Invalid JSON document. Expected an object.";
            ok = false;
            }
    } else
        {
            qDebug() << "Failed to open file to read";
            ok = false;
        }
    return ok;
}

bool JsonHandler::SetTransactionHistory(const QString &filename, const QString &UserName, const QString &Transaction)
{
    // Set mutex for thread safety
    QMutexLocker locker(&mutex);

    bool ok = false;
    QFile file(filename);
    if ( file.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        // Parse Json Doc
        QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll());
        file.close();
        //  Check if the JSON document is an object
        if (jsonDoc.isObject())
        {
            // Set json doc to a json object
            QJsonObject jsonObject = jsonDoc.object();
            // Set Current Date and Time
            QDateTime CurrentDataTime = QDateTime::currentDateTime();
            // Save Date and Time as String
            QString DateNTime = CurrentDataTime.toString("yyyy-MM-dd hh:mm:ss");

            // Set Json Object To save the Transaction array
            QJsonObject TransactionObject;
            // Set Transaction Date n Time
            TransactionObject["Date"] = DateNTime;
            // Set Amount
            TransactionObject["Amount"] = Transaction;
            // Check if the specified object key exists and is an object
            if(jsonObject.contains(UserName) && jsonObject[UserName].isObject())
            {
                // Choose user and set it as a json object
                QJsonObject User = jsonObject[UserName].toObject();
                //check if it has a previous transaction history
                if( !User.contains("Transaction History") )
                {
                    //Create new Field "Transaction History" as an array
                    User["Transaction History"] = QJsonArray();
                }
                // Fetch "Transaction History" Data as an array
                QJsonArray TransHistoryArr = User["Transaction History"].toArray();
                // Prepend this Transaction to the Already existing History
                TransHistoryArr.prepend(TransactionObject);
                // save the new Transaction History
                User["Transaction History"] = TransHistoryArr;
                // Save the new user object to the whole json file
                jsonObject[UserName] = User;

                // Write to the json file to save it
                if( file.open(QIODevice::WriteOnly | QIODevice::Text) )
                {
                    // initialze a new json doc with the updated field value
                    QJsonDocument modifiedJsonDoc(jsonObject);
                    // write to the file to save the new json doc
                    file.write(modifiedJsonDoc.toJson());
                    file.close();
                    ok = true;
                }else {
                    qDebug() << "Error: Unable to open the file for writing.";
                    ok = false;
                }
            }else {
                qDebug() << "Error: Object key not found or not an object.";
                ok = false;
            }
        } else{
            qDebug() << "Invalid JSON document. Expected an object.";
            ok = false;
        }
    }else
    {
        qDebug() << "Failed to open file to read";
        ok = false;
    }
    return ok;
}

bool JsonHandler::GetTransactionHistory(const QString &filename, const QString &UserName, const QString Count, QString &HistoryData)
{
    // Set mutex for thread safety
    QMutexLocker locker(&mutex);

    bool ok = false;
    // set file
    QFile file(filename);
    //Open file to read its contents
    if ( file.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        // Parse Json Doc
        QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll());
        file.close();
        //  Check if the JSON document is an object
        if (jsonDoc.isObject())
        {
            // Set json doc to a json object
            QJsonObject jsonObject = jsonDoc.object();
            // Check if the specified object key exists and is an object
            if(jsonObject.contains(UserName) && jsonObject[UserName].isObject())
            {
                // Take specified user and turn it into a json object
                QJsonObject User = jsonObject[UserName].toObject();
                // Check if User contains a Transaction History
                if( User.contains("Transaction History") )
                {
                    //Create a json Array to access its elements
                    QJsonArray TransactionArray = User["Transaction History"].toArray();
                    QString TransactionData;
                    // access the array
                    qint16 HistoryNum = static_cast<qint16>(Count.toInt()); // cuz qMin must take the same type to work
                    for(qint16 i=0; i < qMin( HistoryNum, static_cast<qint16>( TransactionArray.size() ) ); i++)
                    {
                        QJsonValue UserValue = TransactionArray.at(i);
                        // Turn the User value to a json object
                        QJsonObject UserObject = UserValue.toObject();
                        // Create a json document from the json object
                        QJsonDocument UserDoc(UserObject);
                        // Save transaction data
                        TransactionData = (UserDoc.toJson(QJsonDocument::Indented));
                        // Remove the '\n' from the
                        QStringList DataLines = TransactionData.split('\n');
                        // iterate from the start of lines to the end of the lines to add new line character
                        // to make it human readable
                        for(const QString &line: DataLines)
                        {
                            HistoryData += line + "\n";
                        }
                    }
                    ok = true;
                }else {
                    qDebug() << "No Transaction History Found";
                    ok = false;
                }
            }else {
                qDebug() << "Error: Object key not found or not an object.";
                ok = false;
            }
        }else{
            qDebug() << "Invalid JSON document. Expected an object.";
            ok = false;
        }
    }else {
        qDebug() << "Failed to open file to read";
        ok = false;
    }

    return ok;
}

bool JsonHandler::CreateNewUser(const QString &fileName, const QString& NewUserName, const QVariantMap &UserData)
{
    // Set mutex for thread safety
    QMutexLocker locker(&mutex);

    bool ok = false;
    //Set file
    QFile file(fileName);
    // Open file and read it as text file
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        // Read all file contnents and then parse it as a json document and then save it in a qjson document ...Read existing JSON data from the file
        QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll());
        // close file
        file.close();
        // Check that json file is successfully read and parsed && contains a valid json object
        if(!jsonDoc.isNull() && jsonDoc.isObject())
        {
            // Convert the JSON object to a QVariantMap
            QVariantMap jsonMap = jsonDoc.object().toVariantMap();
            // Add the new object to the QVariantMap
            jsonMap[NewUserName] = UserData;
            // Convert the QVariantMap back to a JSON object
            QJsonObject jsonObj = QJsonObject::fromVariantMap(jsonMap);
            // Open the file for writing
            if (file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                // Write the modified JSON data back to the file
                file.write(QJsonDocument(jsonObj).toJson());
                file.close();
                // New User Added
                ok = true;
            }else {
                qDebug() << "Failed to open file for writing:" << file.errorString();
                ok = false;
            }
        }else{
            qDebug() << "Failed to parse JSON data from" << fileName;
            ok = false;
        }
    }else{
        qDebug() << "Failed to open file for reading:" << file.errorString();
        ok = false;
    }
    return ok;
}

QString JsonHandler::AccountNumberGenerator(const QString &UserName)
{
    // Set mutex for thread safety
    QMutexLocker locker(&mutex);
    return QString::number( qHash(UserName) );
}





