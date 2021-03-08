//
//  Item+CoreDataProperties.swift
//  OriginShopList
//
//  Created by Gabriela Pokropska on 29/09/2020.
//  Copyright © 2020 Gabriela Pokropska. All rights reserved.
//
//

import Foundation
import CoreData


extension Item {

    @nonobjc public class func fetchRequest() -> NSFetchRequest<Item> {
        return NSFetchRequest<Item>(entityName: "Item")
    }

    @NSManaged public var id_item: UUID?
    @NSManaged public var name: String?
    @NSManaged public var origin: Shop?
    
    public var wrappedName: String {
        name ?? "Unknown name"
    }
    
}
