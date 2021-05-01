//  To parse this JSON data, first install
//
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     welcome data = nlohmann::json::parse(jsonString);

#pragma once

#include "nlohmann/json.hpp"

#include <unordered_map>

#ifndef NLOHMANN_OPT_HELPER
#define NLOHMANN_OPT_HELPER
namespace nlohmann {
    template <typename T>
    struct adl_serializer<std::shared_ptr<T>> {
        static void to_json(json & j, const std::shared_ptr<T> & opt) {
            if (!opt) j = nullptr; else j = *opt;
        }

        static std::shared_ptr<T> from_json(const json & j) {
            if (j.is_null()) return std::unique_ptr<T>(); else return std::unique_ptr<T>(new T(j.get<T>()));
        }
    };
}
#endif

namespace trellis {
    using nlohmann::json;

    inline json get_untyped(const json & j, const char * property) {
        if (j.find(property) != j.end()) {
            return j.at(property).get<json>();
        }
        return json();
    }

    inline json get_untyped(const json & j, std::string property) {
        return get_untyped(j, property.data());
    }

    template <typename T>
    inline std::shared_ptr<T> get_optional(const json & j, const char * property) {
        if (j.find(property) != j.end()) {
            return j.at(property).get<std::shared_ptr<T>>();
        }
        return std::shared_ptr<T>();
    }

    template <typename T>
    inline std::shared_ptr<T> get_optional(const json & j, std::string property) {
        return get_optional<T>(j, property.data());
    }

    struct birthdayRange {
        std::shared_ptr<std::string> start;
        std::shared_ptr<std::string> end;
    };

    enum class driversLicenseStatus : int { validUsLicense };

    enum class gender : int { female, male };

    enum class middleName : int { a, b, c, empty, g, h, i, k, l, m, n, r, t, u, x, z };

    struct name {
        std::string firstName;
        middleName middleName;
        std::string lastName;
    };

    enum class relationship : int { child, namedInsured, spouse };

    struct operatorElement {
        bool isPrimary;
        name name;
        birthdayRange birthdayRange;
        gender gender;
        std::shared_ptr<std::string> driversLicenseState;
        std::shared_ptr<driversLicenseStatus> driversLicenseStatus;
        std::shared_ptr<std::string> driversLicenseNumber;
        relationship relationship;
    };

    enum class secUnitType : int { apt, suite };

    enum class suffix : int { e, n, s, w };

    struct address {
        std::shared_ptr<std::string> number;
        std::shared_ptr<std::string> street;
        std::shared_ptr<suffix> suffix;
        std::string city;
        std::string state;
        std::string zip;
        std::shared_ptr<std::string> type;
        std::shared_ptr<secUnitType> secUnitType;
        std::shared_ptr<std::string> secUnitNum;
        std::shared_ptr<std::string> plus4;
    };

    struct policyHolder {
        name name;
        address address;
        std::shared_ptr<std::string> email;
        std::shared_ptr<std::string> phoneNumber;
    };

    struct welcomeElement {
        std::string policyId;
        std::string issuer;
        std::string issueDate;
        std::string renewalDate;
        int64_t policyTermMonths;
        int64_t premiumCents;
        policyHolder policyHolder;
        std::vector<operatorElement> operators;
    };

    using welcome = std::vector<welcomeElement>;
}

namespace trellis {
    using welcome = std::vector<welcomeElement>;
}

namespace nlohmann {
    void from_json(const json & j, trellis::birthdayRange & x);
    void to_json(json & j, const trellis::birthdayRange & x);

    void from_json(const json & j, trellis::name & x);
    void to_json(json & j, const trellis::name & x);

    void from_json(const json & j, trellis::operatorElement & x);
    void to_json(json & j, const trellis::operatorElement & x);

    void from_json(const json & j, trellis::address & x);
    void to_json(json & j, const trellis::address & x);

    void from_json(const json & j, trellis::policyHolder & x);
    void to_json(json & j, const trellis::policyHolder & x);

    void from_json(const json & j, trellis::welcomeElement & x);
    void to_json(json & j, const trellis::welcomeElement & x);

    void from_json(const json & j, trellis::driversLicenseStatus & x);
    void to_json(json & j, const trellis::driversLicenseStatus & x);

    void from_json(const json & j, trellis::gender & x);
    void to_json(json & j, const trellis::gender & x);

    void from_json(const json & j, trellis::middleName & x);
    void to_json(json & j, const trellis::middleName & x);

    void from_json(const json & j, trellis::relationship & x);
    void to_json(json & j, const trellis::relationship & x);

    void from_json(const json & j, trellis::secUnitType & x);
    void to_json(json & j, const trellis::secUnitType & x);

    void from_json(const json & j, trellis::suffix & x);
    void to_json(json & j, const trellis::suffix & x);

    inline void from_json(const json & j, trellis::birthdayRange& x) {
        x.start = trellis::get_optional<std::string>(j, "start");
        x.end = trellis::get_optional<std::string>(j, "end");
    }

    inline void to_json(json & j, const trellis::birthdayRange & x) {
        j = json::object();
        j["start"] = x.start;
        j["end"] = x.end;
    }

    inline void from_json(const json & j, trellis::name& x) {
        x.firstName = j.at("firstName").get<std::string>();
        x.middleName = j.at("middleName").get<trellis::middleName>();
        x.lastName = j.at("lastName").get<std::string>();
    }

    inline void to_json(json & j, const trellis::name & x) {
        j = json::object();
        j["firstName"] = x.firstName;
        j["middleName"] = x.middleName;
        j["lastName"] = x.lastName;
    }

    inline void from_json(const json & j, trellis::operatorElement& x) {
        x.isPrimary = j.at("isPrimary").get<bool>();
        x.name = j.at("name").get<trellis::name>();
        x.birthdayRange = j.at("birthdayRange").get<trellis::birthdayRange>();
        x.gender = j.at("gender").get<trellis::gender>();
        x.driversLicenseState = trellis::get_optional<std::string>(j, "driversLicenseState");
        x.driversLicenseStatus = trellis::get_optional<trellis::driversLicenseStatus>(j, "driversLicenseStatus");
        x.driversLicenseNumber = trellis::get_optional<std::string>(j, "driversLicenseNumber");
        x.relationship = j.at("relationship").get<trellis::relationship>();
    }

    inline void to_json(json & j, const trellis::operatorElement & x) {
        j = json::object();
        j["isPrimary"] = x.isPrimary;
        j["name"] = x.name;
        j["birthdayRange"] = x.birthdayRange;
        j["gender"] = x.gender;
        j["driversLicenseState"] = x.driversLicenseState;
        j["driversLicenseStatus"] = x.driversLicenseStatus;
        j["driversLicenseNumber"] = x.driversLicenseNumber;
        j["relationship"] = x.relationship;
    }

    inline void from_json(const json & j, trellis::address& x) {
        x.number = trellis::get_optional<std::string>(j, "number");
        x.street = trellis::get_optional<std::string>(j, "street");
        x.suffix = trellis::get_optional<trellis::suffix>(j, "suffix");
        x.city = j.at("city").get<std::string>();
        x.state = j.at("state").get<std::string>();
        x.zip = j.at("zip").get<std::string>();
        x.type = trellis::get_optional<std::string>(j, "type");
        x.secUnitType = trellis::get_optional<trellis::secUnitType>(j, "sec_unit_type");
        x.secUnitNum = trellis::get_optional<std::string>(j, "sec_unit_num");
        x.plus4 = trellis::get_optional<std::string>(j, "plus4");
    }

    inline void to_json(json & j, const trellis::address & x) {
        j = json::object();
        j["number"] = x.number;
        j["street"] = x.street;
        j["suffix"] = x.suffix;
        j["city"] = x.city;
        j["state"] = x.state;
        j["zip"] = x.zip;
        j["type"] = x.type;
        j["sec_unit_type"] = x.secUnitType;
        j["sec_unit_num"] = x.secUnitNum;
        j["plus4"] = x.plus4;
    }

    inline void from_json(const json & j, trellis::policyHolder& x) {
        x.name = j.at("name").get<trellis::name>();
        x.address = j.at("address").get<trellis::address>();
        x.email = trellis::get_optional<std::string>(j, "email");
        x.phoneNumber = trellis::get_optional<std::string>(j, "phoneNumber");
    }

    inline void to_json(json & j, const trellis::policyHolder & x) {
        j = json::object();
        j["name"] = x.name;
        j["address"] = x.address;
        j["email"] = x.email;
        j["phoneNumber"] = x.phoneNumber;
    }

    inline void from_json(const json & j, trellis::welcomeElement& x) {
        x.policyId = j.at("policyId").get<std::string>();
        x.issuer = j.at("issuer").get<std::string>();
        x.issueDate = j.at("issueDate").get<std::string>();
        x.renewalDate = j.at("renewalDate").get<std::string>();
        x.policyTermMonths = j.at("policyTermMonths").get<int64_t>();
        x.premiumCents = j.at("premiumCents").get<int64_t>();
        x.policyHolder = j.at("policyHolder").get<trellis::policyHolder>();
        x.operators = j.at("operators").get<std::vector<trellis::operatorElement>>();
    }

    inline void to_json(json & j, const trellis::welcomeElement & x) {
        j = json::object();
        j["policyId"] = x.policyId;
        j["issuer"] = x.issuer;
        j["issueDate"] = x.issueDate;
        j["renewalDate"] = x.renewalDate;
        j["policyTermMonths"] = x.policyTermMonths;
        j["premiumCents"] = x.premiumCents;
        j["policyHolder"] = x.policyHolder;
        j["operators"] = x.operators;
    }

    inline void from_json(const json & j, trellis::driversLicenseStatus & x) {
        if (j == "ValidUSLicense") x = trellis::driversLicenseStatus::validUsLicense;
        else throw "Input JSON does not conform to schema";
    }

    inline void to_json(json & j, const trellis::driversLicenseStatus & x) {
        switch (x) {
            case trellis::driversLicenseStatus::validUsLicense: j = "ValidUSLicense"; break;
            default: throw "This should not happen";
        }
    }

    inline void from_json(const json & j, trellis::gender & x) {
        if (j == "female") x = trellis::gender::female;
        else if (j == "male") x = trellis::gender::male;
        else throw "Input JSON does not conform to schema";
    }

    inline void to_json(json & j, const trellis::gender & x) {
        switch (x) {
            case trellis::gender::female: j = "female"; break;
            case trellis::gender::male: j = "male"; break;
            default: throw "This should not happen";
        }
    }

    inline void from_json(const json & j, trellis::middleName & x) {
        static std::unordered_map<std::string, trellis::middleName> enumValues {
            {"A", trellis::middleName::a},
            {"B", trellis::middleName::b},
            {"C", trellis::middleName::c},
            {"", trellis::middleName::empty},
            {"G", trellis::middleName::g},
            {"H", trellis::middleName::h},
            {"I", trellis::middleName::i},
            {"K", trellis::middleName::k},
            {"L", trellis::middleName::l},
            {"M", trellis::middleName::m},
            {"N", trellis::middleName::n},
            {"R", trellis::middleName::r},
            {"T", trellis::middleName::t},
            {"U", trellis::middleName::u},
            {"X", trellis::middleName::x},
            {"Z", trellis::middleName::z},
        };
        auto iter = enumValues.find(j.get<std::string>());
        if (iter != enumValues.end()) {
            x = iter->second;
        }
    }

    inline void to_json(json & j, const trellis::middleName & x) {
        switch (x) {
            case trellis::middleName::a: j = "A"; break;
            case trellis::middleName::b: j = "B"; break;
            case trellis::middleName::c: j = "C"; break;
            case trellis::middleName::empty: j = ""; break;
            case trellis::middleName::g: j = "G"; break;
            case trellis::middleName::h: j = "H"; break;
            case trellis::middleName::i: j = "I"; break;
            case trellis::middleName::k: j = "K"; break;
            case trellis::middleName::l: j = "L"; break;
            case trellis::middleName::m: j = "M"; break;
            case trellis::middleName::n: j = "N"; break;
            case trellis::middleName::r: j = "R"; break;
            case trellis::middleName::t: j = "T"; break;
            case trellis::middleName::u: j = "U"; break;
            case trellis::middleName::x: j = "X"; break;
            case trellis::middleName::z: j = "Z"; break;
            default: throw "This should not happen";
        }
    }

    inline void from_json(const json & j, trellis::relationship & x) {
        if (j == "Child") x = trellis::relationship::child;
        else if (j == "Named Insured") x = trellis::relationship::namedInsured;
        else if (j == "Spouse") x = trellis::relationship::spouse;
        else throw "Input JSON does not conform to schema";
    }

    inline void to_json(json & j, const trellis::relationship & x) {
        switch (x) {
            case trellis::relationship::child: j = "Child"; break;
            case trellis::relationship::namedInsured: j = "Named Insured"; break;
            case trellis::relationship::spouse: j = "Spouse"; break;
            default: throw "This should not happen";
        }
    }

    inline void from_json(const json & j, trellis::secUnitType & x) {
        if (j == "Apt") x = trellis::secUnitType::apt;
        else if (j == "Suite") x = trellis::secUnitType::suite;
        else throw "Input JSON does not conform to schema";
    }

    inline void to_json(json & j, const trellis::secUnitType & x) {
        switch (x) {
            case trellis::secUnitType::apt: j = "Apt"; break;
            case trellis::secUnitType::suite: j = "Suite"; break;
            default: throw "This should not happen";
        }
    }

    inline void from_json(const json & j, trellis::suffix & x) {
        if (j == "E") x = trellis::suffix::e;
        else if (j == "N") x = trellis::suffix::n;
        else if (j == "S") x = trellis::suffix::s;
        else if (j == "W") x = trellis::suffix::w;
        else throw "Input JSON does not conform to schema";
    }

    inline void to_json(json & j, const trellis::suffix & x) {
        switch (x) {
            case trellis::suffix::e: j = "E"; break;
            case trellis::suffix::n: j = "N"; break;
            case trellis::suffix::s: j = "S"; break;
            case trellis::suffix::w: j = "W"; break;
            default: throw "This should not happen";
        }
    }
}
