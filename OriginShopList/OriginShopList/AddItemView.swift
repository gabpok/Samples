//
//  AddItemView.swift
//  OriginShopList
//
//  Created by Gabriela Pokropska on 29/09/2020.
//  Copyright © 2020 Gabriela Pokropska. All rights reserved.
//

import SwiftUI
import CoreData

struct AddItemView: View {
    @Environment(\.managedObjectContext) var moc
    @Environment(\.presentationMode) var presentation
    
    @State private var itemName: String = ""
    
    let shop: Shop
    
    var body: some View {
        UINavigationBar.appearance().largeTitleTextAttributes = [.foregroundColor: UIColor(named: "title")!]
        UINavigationBar.appearance().titleTextAttributes = [.foregroundColor: UIColor(named: "title")!]
        
        return NavigationView {
            VStack(alignment: .center, spacing: 15) {
                TextField("Item", text: $itemName)
                    .padding()
                    .background(Color("background_textfield"))
                    .frame(width: 400, height: 50)
                
                Button("Save") {
                    let item = Item(context: self.moc)
                    item.name = self.itemName
                    item.origin = self.shop
                    item.origin?.listName = self.shop.listName
                    item.origin?.localization = self.shop.localization
                    
                    try? self.moc.save()
                    self.presentation.wrappedValue.dismiss()
                }.font(.headline)
                .foregroundColor(Color("text"))
                .padding()
                .frame(width: 150, height: 50)
                .background(Color("background_button"))
                .cornerRadius(15.0)
                
                Button("Cancel") {
                    self.presentation.wrappedValue.dismiss()
                }.font(.headline)
                .foregroundColor(Color("text"))
                .padding()
                .frame(width: 150, height: 50)
                .background(Color("background_button"))
                .cornerRadius(15.0)
            }
        }.navigationBarTitle("Add item")
    }
}

struct AddItemView_Previews: PreviewProvider {
    static let moc = NSManagedObjectContext(concurrencyType: .mainQueueConcurrencyType)
    
    static var previews: some View {
        let shop = Shop(context: moc)
        return NavigationView {
            AddItemView(shop: shop)
        }
    }
}
