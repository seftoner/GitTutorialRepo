#ifndef SQLITEQUERY_H
#define SQLITEQUERY_H

const QString kFrnKeys = "PRAGMA foreign_keys = ON;";

const QString kCreateQueryHistroyTable = "CREATE TABLE QueryHistory ("
        "id INTEGER PRIMARY KEY,"
        "queryDate DATETIME,"
        "desiredKnowledge TEXT,"
        "desiredUniversity TEXT,"
        "desiredCity TEXT,"
        "desiredCountry TEXT,"
        "desiredResourceName TEXT)";

const QString kCreateQueryResultTable = "CREATE TABLE QueryResult ("
        "id INTEGER PRIMARY KEY,"
        "name TEXT,"
        "surname TEXT,"
        "position TEXT,"
        "city TEXT,"
        "university TEXT,"
        "phone TEXT,"
        "email TEXT,"
        "skype TEXT,"
        "profileUrl TEXT,"
        "searchResourceName TEXT,"
        "queryHistoryId INTEGER NOT NULL  REFERENCES QueryHistory(Id) ON DELETE CASCADE)";

const QString kGetAllQueryHistroy = "SELECT id, queryDate, desiredKnowledge, desiredUniversity,"
        "desiredUniversity, desiredCity, desiredCountry, desiredResourceName FROM QueryHistory";

const QString kGetQueryResultById = "SELECT name, surname, position, city,"
        "university, phone, email, skype, profileUrl, searchResourceName,"
        "id FROM QueryResult WHERE queryHistoryId = :id";

const QString kAddNewQueryHistoryRecord = "INSERT INTO QueryHistory (queryDate,"
        "desiredKnowledge, desiredUniversity, desiredCity, desiredCountry,"
        "desiredResourceName) "
        "VALUES(:queryDate, :desiredKnowledge, :desiredUniversity, :desiredCity,"
        ":desiredCountry, :desiredResourceName)";

const QString kAddNewQueryResultsRecords = "INSERT INTO QueryResult (name, surname,"
        "position, city, university, phone, email, skype, profileUrl, searchResourceName,"
        "queryHistoryId) "
        "VALUES(:name, :surname, :position, :city, :university, :phone, :email,"
        ":skype, :profileUrl, :searchResourceName, :queryHistoryId)";

const QString kRemoveQueryHistroyRow = "DELETE FROM QueryHistory WHERE id = :id";

const QString kCreateCountriesTable = "CREATE  TABLE 'Countries' "
        "('id' VARCHAR PRIMARY KEY  NOT NULL , 'title' VARCHAR NOT NULL )";

const QString kCreateCitiesTable = "CREATE  TABLE 'Cities' ('title' VARCHAR,"
        "'countryId' VARCHAR REFERENCES Countries(id) ON DELETE CASCADE)";

#endif // SQLITEQUERY_H
